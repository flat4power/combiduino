
//----------------------------------------------------------
//         Calcul de l'injection
//----------------------------------------------------------

void calcul_injection(){
#if INJECTION_USED == 1  
 
  // le temps d'injection est :  temps d'ouverture injecteur + le max a pleine puissance (Req_Fuel) * VE de la map en % * Correction enrichissement en % * corection lambda en %
  
  injection_time_us =  Req_Fuel_us  
  * (VE_MAP(engine_rpm_average, map_pressure_kpa)/float(100) )
  * (MAP_ACCEL(MAP_accel) /float(100)  )
  ;
tick_injection  = ( injection_time_us * prescalertimer5 ) + injector_opening_time_us * prescalertimer5 ;
 #endif
  }



// ----------------------------------------------------------
// recherche du coefficient VE a appliquer suivant la MAP
// ----------------------------------------------------------
int VE_MAP(int rpm, int pressure){
  int map_rpm_index_low = decode_rpm(rpm);                      // retrouve index RPM inferieur
  int map_rpm_index_high = 0;
  int map_pressure_index_low = decode_pressure(pressure);       // retrouve index pression inferieur
  int map_pressure_index_high = 0;
  int VE_min = 0;
  int VE_max = 0;
  int VE = 0;
  
  
  // calcul des valeurs des bin superieur
  if ((map_rpm_index_low >= nombre_point_RPM)|| (rpm <= rpm_axis[0]) ) { // si on est > a tour maxi ou si on est < a tour mini high = low
    map_rpm_index_high = map_rpm_index_low;
  } else{  
    map_rpm_index_high = map_rpm_index_low + 1;
  }
  
  if ((map_pressure_index_low >= nombre_point_DEP) || (pressure <= pressure_axis[0])) { // si on est > a kpa maxi ou si on est < a kpa mini high = low
    map_pressure_index_high = map_pressure_index_low;
  } else{  
    map_pressure_index_high = map_pressure_index_low + 1;
  }  
  
  // gestion de la multi cartographie 
//  map_pressure_index_low = map_pressure_index_low + (carto * nombre_point_DEP) ; // on decale de X lignes
//  map_pressure_index_high = map_pressure_index_high + (carto * nombre_point_DEP) ; // on decale de X lignes
 
 
 // interpolation entre les 4 valeurs de la map
 //            lowRPM      highRPM
 // lowkpa      A              B        VE_min = interpolation A et B
 // highjpa     C              D        VE_max = interpolation C et D
 
 // d'abord VE versus RPM
 if (map_rpm_index_low != map_rpm_index_high){ // si < x tour/min ou > y tour/min -> si on est dans la MAP
 VE_min = map(rpm,
 rpm_axis[map_rpm_index_low],rpm_axis[map_rpm_index_high],
 fuel_map [map_pressure_index_low] [map_rpm_index_low],fuel_map [map_pressure_index_low] [map_rpm_index_high]);
  VE_max = map(rpm,
 rpm_axis[map_rpm_index_low],rpm_axis[map_rpm_index_high],
 fuel_map [map_pressure_index_high] [map_rpm_index_low],fuel_map [map_pressure_index_high] [map_rpm_index_high]);
 }else{
   VE_min = fuel_map [map_pressure_index_low] [map_rpm_index_low];
   VE_max = fuel_map [map_pressure_index_high] [map_rpm_index_low];
 }
 
 // puis entre VE_min / max et kpa
  if (map_pressure_index_low != map_pressure_index_high){
  VE = map(pressure
  ,pressure_axis[map_pressure_index_low],pressure_axis[map_pressure_index_high],
  VE_min,VE_max);
  }else{
    VE = VE_min;
  }  
  
//debug("VE:"+String(VE) + " VE_min:"+ String(VE_min) + " VE_max:" + String(VE_max));  
return VE;
}

//----------------------------------------------------
//     Gestion de l'enrichiseemnt a l'acceleration
//----------------------------------------------------

// renvoi une valeur dependante de l'acceleration (kpa/s ) 
// on compare l'acceleration avec le tableau MAP_kpas
// on renvoie l'enrichissement du tableau MAP_acceleration
int MAP_ACCEL(int MAP_accel_){
   int extrafuel = 100; // 100 = Pas d'enrichissement
   int bin = 0;
   if(MAP_accel_ <MAP_kpas[0]){                // check si on est dans les limites haute/basse
     bin = 0;
     extrafuel = MAP_acceleration[0];
   } else { 
     if(MAP_accel_ >=MAP_kpas[MAP_acc_max -1]) {      // 
       bin = MAP_acc_max -1;
       extrafuel = MAP_acceleration[MAP_acc_max -1];     
     }else{
       // retrouve la valeur inferieur 
       while(MAP_accel_ > MAP_kpas[bin]){bin++;} // du while
       if (bin > 0){bin--;}
       extrafuel = MAP_acceleration[bin];
     }
    return extrafuel;
  }
  
  return extrafuel;
  }


//-----------------------------------------------------------
//           Gestion de la sonde lambda
//-----------------------------------------------------------

// gestion de la lecture de la lambda
void lecturelambda(){
 int afr_lu = 0;
 int point_afr = 0;
 
 analogReference(INTERNAL1V1);
 afr_lu = analogRead(pin_lambda);   
 analogReference(DEFAULT);
 
if (afr_lu > AFR_analogique[AFR_bin_max -1]) { // borne maxi  
   // AFR_actuel = AFR[point_afr];
}  else if (afr_lu <AFR_analogique[0]){ // borne mini
    // AFR_actuel = AFR[0];
} else {
    point_afr = decode_afr(afr_lu);
    AFR_actuel = map(afr_lu,AFR_analogique[point_afr],AFR_analogique[point_afr + 1],AFR[point_afr],AFR[point_afr + 1]) ; // on fait une interpolation
}
} 


 // Renvoi le bin AFR (0 -> 7)
int decode_afr(int afr_) {
  int map_afr = 0;
   if(afr_ <AFR_analogique[0]){                // check si on est dans les limites haute/basse
     map_afr = 0;
   } else { 
     if(afr_ >=AFR_analogique[AFR_bin_max -1]) {      // 
       map_afr = AFR_bin_max - 1;      
     }else{
       // retrouve la valeur inferieur 
       while(afr_ > AFR_analogique[map_afr]){map_afr++;} // du while
       if (map_afr > 0){map_afr--;}
     }
    return map_afr;
  }
  return map_afr;
}

void checkpump(){
  // check si le moteur tourne
  if ( (micros() - pip_old) > 100000){
    engine_rpm_average = 0;
  }
  // check pour arreter la pompe
  if (engine_rpm_average > 1){
    digitalWrite(pin_pump,LOW); 
  }else{
    digitalWrite(pin_pump,HIGH);
  }
}
