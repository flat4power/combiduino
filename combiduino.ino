#pragma GCC optimize ("-O2")

#define INJECTION_USED  1  // 1 si OUI sinon 0
#define LAMBDA_USED  1  // 1 si OUI sinon 0
#define KNOCK_USED  0  // 1 si OUI sinon 0
#define LAMBDATYPE 1  // 1= pour wideband 2= pour Narrow band
#define VACUUMTYPE 1  // 1= pour prise depression colecteur 2= pour prise depression amont papillon 
const byte VERSION= 9;   //version du combiduino
//-------------------------------------------- Include Files --------------------------------------------//
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <SPI.h>
#include <boards.h>
#include <RBL_nRF8001.h>


#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
//-------------------------------------------- Global variables --------------------------------------------//
//declaration des pins
const int interrupt_X = 3;      // PIP EDIS pin
const int BLE_reset_pin = 4;     // pin 4 reboot BLE
const int pin_pump = 5;              // pin 5 activation de la pompe 
// pin 8 et 9 BLE

const int pin_injection = 11; // pin pour la carte MOSFET Injecteur
const int pin_ignition = 12;  // pin du début d'ignition pour le knock
const int SAW_pin = 13;           // SAW EDIS pin

const int MAP_pin = A0;            // depression
const int pin_lambda = A5;         // Signal lambda




// gestion different mode du moteur
#define Stopping 1
#define Cranking  2
#define Idling  3
#define Running  10


byte running_mode = Stopping;

// declaration pour injection 
const byte ouverture_initiale = 6 ; // nombre de millisecond d'ouverture des injecteurs avant démarrage
volatile unsigned int tick_injection = 0; // pour le timer
const byte nombre_inj_par_cycle = 2; // le nombre d'injection pour 1 cycle complet 2 tour
unsigned int Req_Fuel_us = 10000 / nombre_inj_par_cycle;  // ouverture max des injecteurs 100% 
unsigned int injection_time_us = 0; // temps d'injection corrigé pour le timer
unsigned int previous_injection_time_us = 0; // temps d'injection corrigé pour le timer
const unsigned int injector_opening_time_us = 800; // temps d'ouverture de l'injecteur en us
volatile unsigned int cylindre_en_cours = 1; // cylindre en cours d'allumage
const boolean cylinder_injection[4] = {true,false,true,false}; // numero de cylindre cylindre pour injection
const byte prescalertimer5 =2 ; //prescaler /8 a 16mhz donc 1us= 2 tick


// declaration acceleration
int MAP_kpas[8] =        {-50,-10,  10,  40,  80,  120}; //valeur acceleration en kpa /s
int MAP_acceleration[8] ={ 0 ,  0,   0,  10,  10,  10} ; //valeur enrichissement en % de reqfuel
const int accel_every_spark = 80;  // correction possible tous les x etincelle
long  last_accel_spark = 0 ; //pas de correction au demarrage
byte accel_state_actuel = 0;  //etat du moteur 0=pas d'accel 1=accel 2=decel 
const int MAP_acc_max = 6; // nombre d'indice du tableua MAP_kpas
unsigned int VE_actuel = 0; // VE du dernier calcul
unsigned int acceleration_actuel = 0; // accel du dernier calcul



// declaration pour la lambda
const int AFR_bin_max = 9;

#if LAMBDATYPE == 2
int AFR_analogique[AFR_bin_max] ={45,   93  ,186 ,214 ,651, 744, 791, 835,1023}; //valeur lu par le capteur avec echelle 1,1V 1024
byte AFR[AFR_bin_max] =          {190 ,170  ,150 ,147 ,140, 130, 120, 110,90} ; //valeur AFR * 10
# endif
#if LAMBDATYPE == 1
int AFR_analogique[AFR_bin_max] ={0 , 200, 300, 400, 540, 664, 716, 818, 1000}; //valeur lu par 0V=9 5V=19
byte AFR[AFR_bin_max] =          {90, 110, 120, 130, 147, 155, 160, 170, 190 } ; //valeur AFR * 10
# endif

int AFR_actuel =147; // valeur AFR 100 -> 190
int max_lambda_cor = 130; // correction maxi
int min_lambda_cor = 50; // correction mini
int correction_lambda_actuel = 100;
boolean correction_lambda_used = false; // correction lambda active ou non
const int increment_correction_lambda = 2;
const int correction_lambda_every_spark = 30;  // correction possible tous les x etincelle
long  last_correction_lambda_spark = 1000 ; //pas de correction au demarrage
int sum_lambda = 0;
byte count_lambda = 0;
const byte nbre_mesure_lambda = 2;


// declaration du debugging
boolean debugging = true; // a mettre a falsdebuge pour ne pas debugger
String debugstring = "";



//----------------------------
//declaration bluetooth
//----------------------------

//const boolean init_BT = true; // pour creer la config BT a mettre a false normalement
char BT_name [10] = "Combi";
String OutputString = "";

//Serial input initailisation
String inputString = "";            // a string to hold incoming data
boolean stringComplete = false;     // whether the string is complete
String inputString3 = "";            // a string to hold incoming data
boolean stringComplete3 = false;     // whether the string is complete

// ----------------------------
// declaration pour l ECU
//-----------------------------
int point_RPM = 0; // index dans la carto
int point_KPA = 0; // index dans la carto
boolean bin_carto_change = true; // indicateur de changement de point de carto

volatile long nbr_spark = 0;
volatile float map_value_us;                 // duree du SAW EDIS en microseconds
volatile boolean SAW_requested = false;
unsigned int rev_limit = 4550;               // Max tour minute
unsigned int rev_mini = 500; // min tour minute
volatile int Degree_Avance_calcul = 10;              // Degree_Avance_calculÃ© suivant la cartographie a10 par defaut pour demmarragee
boolean output = true;
boolean fixed = false;              // declare whether to use fixed advance values
const int fixed_advance = 15;             // Avance fixe
boolean multispark = true;         // multispark
volatile boolean first_multispark = true;         // 1er allumage en multispark
int correction_degre = 0; // correction de la MAP
volatile unsigned int tick = 0; // nombre de tick du timer pour le saw
const int msvalue = 2025 ; // normaly 2048 
volatile boolean newvalue = true;  // check si des nouvelles valeurs RPM/pression ont ete calculÃ©s
//gestion simplifie des rpm
volatile unsigned long timeold = 0;
const unsigned int debounce = 4000; // temps mini acceptable entre 2 pip 4ms-> 7500 tr/min 
volatile unsigned long pip_old = 0; // durée du dernier pip pour le debounce
volatile unsigned int pip_count = 0;
volatile unsigned int engine_rpm_average = 0;  // Initial average engine rpm pour demarrage
const unsigned int maxpip_count = 20;  //on fait la moyenne tout les x pip
const int nombre_point_RPM = 23; // nombre de point de la MAP
const int nombre_point_DEP = 17; // nombre de point de la MAP
const int nombre_carto_max = 5; // nombre de carto a stocker
int carto_actuel = 1; //cartographie en cours
volatile boolean ignition_on = false; // gere si le SAW est envoyé non terminé

// declaration pour le KNOCK
#if KNOCK_USED == 1
long knockvalue[23] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // accumulation des valuer de knock
long knockcount[23] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // accumulation des count de knock
long knockmoyen[23] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // accumulation des count moyen
long total_knock = 0;
long knock_moyen = 0; // moyend de la période
int count_knock = 0;
int delta_knock = 0; // ecart par rapport a la moyenne enregistré
const int count_knock_max = 8; // tout les 8 pip = 4 tour
boolean knock_record = false; // enregistrement des valeur normal du capteur
boolean knock_active = false; // utilisation de la fonction knock
#endif

// variable pression moyenne

int correction_pressure = 400;   // gestion de la valeur du capteur a pression atmo se met a jour lors de lancement
int map_pressure_kpa = 100;
int pressure_kpa_ADC= 1000;
int previous_map_pressure_kpa = 100;
int MAP_accel = 100 ;  // kpa/s d'acceleration
int sum_pressure = 0;
byte count_pressure = 0;
const byte nbre_mesure_pressure = 5;
const int MAP_check_per_S = 8 ; // nombre de calcul par seconde d'acceleration / depression
const int kpa_0V = 0; // Kpa reel lorsque le capteur indique 0V
long temp_spark_dep = 0;

// variable de loop
long var1 = 0;
long var2 = 0;
unsigned long time_loop = 0;
unsigned long time_reception = 0;
const unsigned long interval_time_reception = 100; // check des ordres tout les 100 ms secondes

unsigned long time_envoi = 0;
const unsigned long interval_time_envoi = 400; // ECU / EC1 toute les 1 secondes
unsigned long time_check_depression = 0;
const unsigned long interval_time_check_depression = 1000 / (MAP_check_per_S * nbre_mesure_pressure); // Depression x fois / seconde
unsigned long time_check_lambda = 0;
const unsigned long interval_time_check_lambda = 100; // lambda 5 fois / seconde
unsigned long time_check_connect = 0; 
const unsigned long interval_time_check_connect = 30000; // reconnection  1 fois /  30 seconde

unsigned long time_check_fuel_pump = 0; 
const unsigned long interval_time_check_fuel_pump = 5000; // check de la pompe de fuel




//----------------------------
// Variable pour eeprom
//----------------------------

const int debut_eeprom = 50; //Pour laisser un peu de vide
const int taille_carto = 500; // carto complete avec kpa + rpm
const int debut_kpa = 400; //Pour ecrire les kpa au 400 de chaque MAP
const int debut_rpm = 420; //Pour ecrire les rpm au 420 de chaque MAP
// gestion parametre de eeprom
const int eprom_carto_actuel = 0; // emplacement dans EEPROM
const int eprom_init = 1; // emplacement dans EEPROM de init =100 OK sinon on ecrase les cartos
const int eprom_nom_BLE = 10; // emplaceement eeprom du  nom du BLE
const int eprom_rev_max = 21; // emplaceement eeprom du  REV MAX
const int eprom_rev_min = 23; // emplaceement eeprom du  REV MIN
const int eprom_debug = 2; // emplaceement eeprom du  debug
const int eprom_knock = 6; // emplaceement eeprom du knock sensor
const int eprom_reboot = 7; // emplacement eeprom du knock moyen

const int eprom_ms = 3; // emplaceement eeprom du  multispark
const int eprom_avance = 4; // emplaceement eeprom de avance initiale
const int eprom_adresseknock = 25; // emplacement eeprom du knock moyen

boolean init_eeprom = true; // si true on re ecrit les carto au demarrage
//-------------------------------------------- Initialise Parameters --------------------------------------------//
void setup() {
  
  // pour ne pas lancer de faux SAW
  detachInterrupt(1);
  detachInterrupt(0); // on desactive le pin 2
  
// declaration des Pin OUTPUT
  pinMode(SAW_pin, OUTPUT);                                                 
  pinMode(pin_ignition, OUTPUT); 
  pinMode(pin_injection, OUTPUT);
  pinMode( pin_pump, OUTPUT);

// gestion de l'allumage de la pompe
digitalWrite(pin_pump,LOW);

// declaration des Pin INTPUT  
  pinMode(interrupt_X, INPUT);
  digitalWrite (interrupt_X, HIGH);
  pinMode(pin_lambda, INPUT);
  digitalWrite (pin_lambda, LOW );
  

  // port serie
  Serial.begin(115200); while (!Serial) { ; }// wait for serial port to connect. 
 
 #if KNOCK_USED == 1  
   Serial1.begin(115200); while (!Serial1) { ; }// wait for serial port to connect. 
 #endif

  inputString.reserve(50);   //reserve 50 bytes for serial input - equates to 25 characters
  OutputString.reserve(50);
 
  time_loop = millis();

  // init des cartos si pas deja fait
  if (EEPROM.read(eprom_init)   !=  VERSION ) { init_eeprom = true; }else{init_eeprom = false;} // on lance l'init de l'eeprom si necessaire   
//---------POUR INIT CARTE -------------------------------  
//  init_eeprom = true; // A DE TAGGER POUR INITIALISATION 
// ------------------------------------------------------     
if (init_eeprom == true) {debug ("Init des MAP EEPROM");init_de_eeprom();RAZknock(); } // on charge les map EEPROM a partir de la RAM et konco moyen
 // lecture des carto
  debug ("Init des MAP RAM");
  read_eeprom(); // on charge les MAP en RAM a partir de l'eeprom et la derniÃ¨re MAP utilisÃ©e
 #if KNOCK_USED == 1
  initknock();
 #endif 

// Initialisationdu BT
   ble_set_name(BT_name); debug ("ready!");ble_begin();  

 initpressure();
 inittimer(); // init des interruption Timer 5

 // initialisation du PIP interrupt 
  attachInterrupt(1, pip_interupt, FALLING);                                //  interruption PIP signal de l'edis

  injection_initiale();

}


//-------------------------------------------- Boucle principal --------------------------------------------//
void loop() {
   time_loop = millis();

// check entree serial
if (time_loop - time_reception > interval_time_reception){checkdesordres();time_reception = time_loop;}

//chek des valeur de knock
       getknock();


// calcul du nouvel angle d avance / injection si des valeurs ont changÃ©s

  if (newvalue == true) {
    calcul_carto();

    newvalue = false; }

// puis on gere les fonctions annexe a declencher periodiquement

  // recalcul de la dÃ©pression
  if (time_loop - time_check_depression > interval_time_check_depression){gestiondepression();time_check_depression = time_loop;}

  // recalcul de la lambda
  if (time_loop - time_check_lambda > interval_time_check_lambda){lecturelambda();time_check_lambda = time_loop;}

// gestions sortie pour module exterieur ECU / EC1
  if (time_loop - time_envoi > interval_time_envoi){gestionsortieECU();gestionsortieEC1();time_envoi = time_loop;}

// gestions connection BLE
  if (time_loop - time_check_connect > interval_time_check_connect){checkBLE();time_check_connect = time_loop;}

// check demarrage de la pompe fuel
  if (time_loop - time_check_fuel_pump > interval_time_check_fuel_pump){checkpump();time_check_fuel_pump = time_loop;}
}

void serialEvent() {
   
 while (Serial.available()) {                    //whilst the serial port is available...
   inputString = Serial.readStringUntil('\n');   //... read in the string until a new line is recieved
   stringComplete = true;                     
 }
 }





void initpressure(){
  correction_pressure = 0;
  // on initialise la pression atmospherique
  for (int j = 0 ; j < 10; j++) { 
    correction_pressure += analogRead(MAP_pin);
  }
 correction_pressure =  (correction_pressure / 10);


}

 void inittimer(){
 // parametrage du timer 5
  TCCR5A = 0;
  TCCR5B = 0;
  TCCR5C = 0;
  TCNT5  = 0;
  TIFR5 = 0x00;
  TIMSK5 = 0 ; 
  TCCR5B |= (1 << CS51);    // 8 prescaler 

// parametrage pour le PIP pin 3 Timer 3C
 TCCR3B |= (1 << ICNC3); // Noise canceler a OUI

 }
 



