

 byte pressure_axis[nombre_carto_max][nombre_point_DEP] = {
 { 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 99}, // 17 carto 1
 { 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 99}, // 17 carto 2
 { 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 99}, // 17 carto 3
 { 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 99}, // 17 carto 4
 { 21, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 99} // 17 carto 5
 };  

 int rpm_axis[nombre_carto_max][nombre_point_RPM]  = {
 {600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000}, // 23 carto 1
 {600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5001}, // 23 carto 2
 {600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000}, // 23 carto 3
 {600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000}, // 23 carto 4
 {600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000} // 23 carto 5
 };
 
 // Global array for the ignition map, with values as degrees of advance
// RPM values seperated into columns, Manifold Pressure (kpa) seperated into rows.
 byte ignition_map [nombre_point_DEP*nombre_carto_max] [nombre_point_RPM] = {
//Carto 1 + depression + RPM
// 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA20
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA25
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA30
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA35
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA40
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA45
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA50
{   25,  21,   21,   24,   27,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA55
{   25,  21,   21,   24,   27,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA60
{   24,  20,   20,   23,   26,   29,   31,   33,   35,   37,   39,   41,   43,   45,   45,   45,   45,   45,   45,   45,   45,   45,   45}, // KPA65
{   23,  19,   19,   22,   25,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA70
{   22,  18,   18,   21,   24,   27,   29,   31,   33,   35,   37,   39,   41,   43,   43,   43,   43,   43,   43,   43,   43,   43,   43}, // KPA75
{   21,  17,   17,   20,   23,   26,   28,   30,   32,   34,   36,   38,   40,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42}, // KPA80
{   20,  16,   16,   19,   22,   25,   27,   29,   31,   33,   35,   37,   39,   41,   41,   41,   41,   41,   41,   41,   41,   41,   41}, // KPA85
{   18,  14,   14,   17,   20,   23,   25,   27,   29,   31,   33,   35,   37,   39,   39,   39,   39,   39,   39,   39,   39,   39,   39}, // KPA90
{   16,  12,   12,   15,   18,   21,   23,   25,   27,   29,   31,   33,   35,   37,   37,   37,   37,   37,   37,   37,   37,   37,   37}, // KPA95
{   14,  10,   10,   13,   16,   19,   21,   23,   25,   27,   29,   31,   33,   35,   35,   35,   35,   35,   35,   35,   35,   35,   35}, // KPA100

//Carto 2 - de RPM + depression
// 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA20
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA25
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA30
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA35
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA40
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA45
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA50
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA55
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA60
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA65
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA70
{   24,  22,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA75
{   22,  20,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42}, // KPA80
{   20,  18,   18,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40}, // KPA85
{   17,  15,   15,   17,   19,   21,   23,   25,   27,   29,   31,   33,   35,   37,   37,   37,   37,   37,   37,   37,   37,   37,   37}, // KPA90
{   14,  12,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   34,   34,   34,   34,   34,   34,   34,   34,   34,   34}, // KPA95
{   12,  11,   11,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32}, // KPA100

//Carto 3 - de RPM + depression
// 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA20
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA25
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA30
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA35
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA40
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA45
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA50
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA55
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA60
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA65
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA70
{   24,  22,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA75
{   22,  20,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42}, // KPA80
{   20,  18,   18,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40}, // KPA85
{   17,  15,   15,   17,   19,   21,   23,   25,   27,   29,   31,   33,   35,   37,   37,   37,   37,   37,   37,   37,   37,   37,   37}, // KPA90
{   14,  12,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   34,   34,   34,   34,   34,   34,   34,   34,   34,   34}, // KPA95
{   12,  11,   11,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32}, // KPA100

//Carto 4 - de RPM + depression
// 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA20
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA25
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA30
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA35
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA40
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA45
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA50
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA55
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA60
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA65
{   26,  24,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA70
{   24,  22,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA75
{   22,  20,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42}, // KPA80
{   20,  18,   18,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40}, // KPA85
{   17,  15,   15,   17,   19,   21,   23,   25,   27,   29,   31,   33,   35,   37,   37,   37,   37,   37,   37,   37,   37,   37,   37}, // KPA90
{   14,  12,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   34,   34,   34,   34,   34,   34,   34,   34,   34,   34}, // KPA95
{   12,  11,   11,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32}, // KPA100


//Carto 5 - RPM  - depression
// 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000

{   24,  22,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA20
{   24,  22,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA25
{   24,  22,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA30
{   24,  22,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA35
{   24,  22,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA40
{   23,  21,   21,   23,   25,   27,   29,   31,   33,   35,   37,   39,   41,   43,   43,   43,   43,   43,   43,   43,   43,   43,   43}, // KPA45
{   22,  20,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42}, // KPA50
{   21,  19,   19,   21,   23,   25,   27,   29,   31,   33,   35,   37,   39,   41,   41,   41,   41,   41,   41,   41,   41,   41,   41}, // KPA55
{   20,  18,   18,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,   40,   40,   40,   40,   40,   40,   40,   40,   40}, // KPA60
{   19,  17,   17,   19,   21,   23,   25,   27,   29,   31,   33,   35,   37,   39,   39,   39,   39,   39,   39,   39,   39,   39,   39}, // KPA65
{   18,  16,   16,   18,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   38,   38,   38,   38,   38,   38,   38,   38,   38}, // KPA70
{   17,  15,   15,   17,   19,   21,   23,   25,   27,   29,   31,   33,   35,   37,   37,   37,   37,   37,   37,   37,   37,   37,   37}, // KPA75
{   16,  14,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   34,   36,   36,   36,   36,   36,   36,   36,   36,   36,   36}, // KPA80
{   15,  13,   13,   15,   17,   19,   21,   23,   25,   27,   29,   31,   33,   35,   35,   35,   35,   35,   35,   35,   35,   35,   35}, // KPA85
{   14,  12,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   34,   34,   34,   34,   34,   34,   34,   34,   34,   34}, // KPA90
{   13,  11,   11,   13,   15,   17,   19,   21,   23,   25,   27,   29,   31,   32,   33,   34,   34,   34,   34,   34,   34,   34,   34}, // KPA95
{   12,  10,   10,   12,   14,   16,   18,   20,   22,   24,   26,   28,   30,   32,   32,   32,   32,   32,   32,   32,   32,   32,   32} // KPA100

};


 byte fuel_map [nombre_point_DEP*1] [nombre_point_RPM] = {
//Carto 1 + depression + RPM
// 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA20
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA25
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA30
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA35
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA40
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA45
{   26,  22,   22,   25,   28,   31,   33,   35,   37,   39,   41,   43,   45,   47,   47,   47,   47,   47,   47,   47,   47,   47,   47}, // KPA50
{   25,  21,   21,   24,   27,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA55
{   25,  21,   21,   24,   27,   30,   32,   34,   36,   38,   40,   42,   44,   46,   46,   46,   46,   46,   46,   46,   46,   46,   46}, // KPA60
{   24,  20,   20,   23,   26,   29,   31,   33,   35,   37,   39,   41,   43,   45,   45,   45,   45,   45,   45,   45,   45,   45,   45}, // KPA65
{   23,  19,   19,   22,   25,   28,   30,   32,   34,   36,   38,   40,   42,   44,   44,   44,   44,   44,   44,   44,   44,   44,   44}, // KPA70
{   22,  18,   18,   21,   24,   27,   29,   31,   33,   35,   37,   39,   41,   43,   43,   43,   43,   43,   43,   43,   43,   43,   43}, // KPA75
{   21,  17,   17,   20,   23,   26,   28,   30,   32,   34,   36,   38,   40,   42,   42,   42,   42,   42,   42,   42,   42,   42,   42}, // KPA80
{   20,  16,   16,   19,   22,   25,   27,   29,   31,   33,   35,   37,   39,   41,   41,   41,   41,   41,   41,   41,   41,   41,   41}, // KPA85
{   18,  14,   14,   17,   20,   23,   25,   27,   29,   31,   33,   35,   37,   39,   39,   39,   39,   39,   39,   39,   39,   39,   39}, // KPA90
{   16,  12,   12,   15,   18,   21,   23,   25,   27,   29,   31,   33,   35,   37,   37,   37,   37,   37,   37,   37,   37,   37,   37}, // KPA95
{   14,  10,   10,   13,   16,   19,   21,   23,   25,   27,   29,   31,   33,   35,   35,   35,   35,   35,   35,   35,   35,   35,   35}// KPA100

};
