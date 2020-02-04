/*
 * hamming_constants.h
 *
 *  Created on: Feb 4, 2020
 *      Author: ECE113DWS20
 */

#ifndef HAMMING_CONSTANTS_H_
#define HAMMING_CONSTANTS_H_

float cos_lookup [1024] = {0.08,0.088856004,0.115083021,0.157671196,0.214980699,0.284804863,0.364455154,0.450864688,0.540706321,0.630520757,0.716849748,0.796369253,0.866017422,0.923112498,0.96545607,0.991417727,0.999997831,0.990866011,0.964373881,0.921541505,0.864018115,0.794018614,0.714238287,0.627749026,0.537881045,0.448094652,0.361847017,0.282459049,0.212987531,0.156107421,0.114008851,0.088312799,
0.080008676,0.089416227,0.11617322,0.159249393,0.216986127,0.287160305,0.367069914,0.453638087,0.54353157,0.633289072,0.719454538,0.798710221,0.868004431,0.924669039,0.96652221,0.991952415,0.999980478,0.990297286,0.963275683,0.919956118,0.862006585,0.791658392,0.711620254,0.624973986,0.535055849,0.445328083,0.359245599,0.280122949,0.2110067,0.154558128,0.112950751,0.087786634,
0.080034705,0.089993448,0.117279407,0.160841954,0.21900374,0.289525284,0.369691197,0.456414743,0.546356686,0.636053869,0.722052558,0.80104143,0.869979067,0.92621107,0.967572261,0.992470053,0.999945774,0.989711575,0.962161517,0.918356399,0.859982907,0.789288678,0.708995746,0.62219574,0.532230839,0.442565085,0.356651001,0.277796653,0.209038279,0.153023375,0.11190876,0.087277527,
0.080078085,0.090587644,0.11840154,0.162448817,0.221033463,0.291899712,0.372318905,0.459194553,0.549181562,0.638815042,0.724643711,0.803362791,0.871941255,0.927738531,0.968606181,0.992970623,0.999893719,0.989108899,0.961031427,0.916742407,0.857947159,0.786909559,0.706364863,0.619414393,0.529406123,0.439805763,0.354063319,0.275480248,0.207082342,0.15150322,0.110882919,0.086785498,
0.080138814,0.091198793,0.119539577,0.164069923,0.223075217,0.294283499,0.374952938,0.46197741,0.552006092,0.641572487,0.727227898,0.805674218,0.873890921,0.929251366,0.969623934,0.993454106,0.999824315,0.988489282,0.959885453,0.915114202,0.855899417,0.784521126,0.703727704,0.616630051,0.526581806,0.43705022,0.351482651,0.273173822,0.205138965,0.14999772,0.109873265,0.086310566,
0.080216891,0.091826873,0.120693476,0.16570521,0.225128927,0.296676555,0.377593198,0.464763211,0.554830169,0.644326101,0.729805023,0.807975622,0.875827991,0.930749516,0.97062548,0.993920483,0.999737566,0.987852746,0.958723641,0.913471848,0.853839759,0.782123469,0.701084369,0.613842817,0.523757995,0.434298561,0.348909094,0.270877461,0.20320822,0.148506932,0.108879837,0.085852749,
0.080312313,0.092471859,0.121863192,0.167354617,0.227194515,0.29907879,0.380239584,0.46755185,0.557653687,0.647075779,0.732374987,0.810266918,0.877752393,0.932232927,0.971610781,0.994369736,0.999633474,0.987199316,0.957546033,0.911815405,0.851768261,0.779716678,0.698434957,0.611052799,0.520934797,0.43155089,0.346342746,0.268591252,0.201290179,0.147030913,0.107902672,0.085412063,
0.080425075,0.093133727,0.123048681,0.169018081,0.229271903,0.301490114,0.382891996,0.470343222,0.560476538,0.649821418,0.734937695,0.812548019,0.879664054,0.933701541,0.972579801,0.99480185,0.999512042,0.986529016,0.956352673,0.910144936,0.849685002,0.777300845,0.695779569,0.6082601,0.518112319,0.428807309,0.343783703,0.266315281,0.199384916,0.145569717,0.106941807,0.084988526,
0.080555174,0.093812452,0.124249899,0.170695539,0.231361013,0.303910435,0.385550335,0.473137222,0.563298618,0.652562915,0.737493048,0.814818838,0.881562902,0.935155304,0.973532502,0.995216807,0.999373277,0.985841872,0.955143608,0.908460503,0.847590061,0.774876059,0.693118304,0.605464826,0.515290666,0.426067923,0.341232062,0.264049635,0.197492501,0.144123401,0.105997278,0.084582154,
0.080702604,0.094508009,0.1254668,0.172386929,0.233461765,0.306339662,0.388214501,0.475933744,0.566119818,0.655300165,0.740040952,0.81707929,0.883448865,0.93659416,0.974468849,0.995614591,0.999217183,0.985137909,0.953918882,0.906762172,0.845483517,0.772442414,0.690451263,0.602667082,0.512469945,0.423332835,0.33868792,0.261794399,0.195613007,0.142692018,0.105069121,0.084192961,
0.080867361,0.095220371,0.126699339,0.174092186,0.235574081,0.308777703,0.390884392,0.478732683,0.568940033,0.658033065,0.74258131,0.819329289,0.885321872,0.938018056,0.975388807,0.995995189,0.999043766,0.984417154,0.952678542,0.905050005,0.843365449,0.77,0.687778547,0.599866974,0.509650262,0.420602148,0.336151371,0.259549657,0.193746505,0.141275624,0.104157371,0.083820962,
0.081049437,0.095949512,0.127947469,0.175811247,0.237697881,0.311224466,0.393559908,0.481533933,0.571759156,0.660761513,0.745114025,0.821568752,0.887181853,0.939426937,0.97629234,0.996358585,0.998853032,0.983679634,0.951422634,0.903324067,0.841235938,0.76754891,0.685100256,0.597064608,0.506831725,0.417875964,0.333622512,0.257315495,0.191893064,0.13987427,0.103262063,0.083466172,
0.081248827,0.096695404,0.129211143,0.177544046,0.239833085,0.31367986,0.396240949,0.484337388,0.574577081,0.663485406,0.747639003,0.823797593,0.889028736,0.94082075,0.977179416,0.996704765,0.998644988,0.982925378,0.950151206,0.901584424,0.839095062,0.765089236,0.682416491,0.59426009,0.504014438,0.415154388,0.331101439,0.255091996,0.190052755,0.13848801,0.102383229,0.083128604,
0.081465522,0.097458018,0.130490313,0.179290517,0.241979611,0.316143791,0.398927412,0.487142944,0.577393702,0.66620464,0.750156149,0.826015728,0.890862454,0.942199443,0.978049999,0.997033718,0.998419644,0.982154412,0.948864306,0.89983114,0.836942904,0.762621071,0.679727354,0.591453524,0.50119851,0.412437522,0.328588246,0.252879245,0.188225647,0.137116896,0.101520904,0.08280827,
0.081699514,0.098237327,0.131784931,0.181050596,0.244137381,0.318616167,0.401619198,0.489950493,0.580208913,0.668919114,0.752665366,0.828223074,0.892682935,0.943562964,0.978904058,0.99734543,0.998177006,0.981366768,0.947561983,0.898064282,0.834779544,0.760144507,0.677032946,0.588645018,0.498384044,0.409725467,0.326083027,0.250677325,0.186411809,0.135760981,0.100675119,0.082505184,
0.081950795,0.0990333,0.133094948,0.182824216,0.24630631,0.321096894,0.404316203,0.49275993,0.583022606,0.671628724,0.755166561,0.830419547,0.894490113,0.944911262,0.97974156,0.997639889,0.997917084,0.980562474,0.946244285,0.896283918,0.832605065,0.75765964,0.674333369,0.585834677,0.495571149,0.407018327,0.323585879,0.248486319,0.184611309,0.134420314,0.099845908,0.082219355,
0.082219355,0.099845908,0.134420314,0.184611309,0.248486319,0.323585879,0.407018327,0.495571149,0.585834677,0.674333369,0.75765964,0.832605065,0.896283918,0.946244285,0.980562474,0.997917084,0.997639889,0.97974156,0.944911262,0.894490113,0.830419547,0.755166561,0.671628724,0.583022606,0.49275993,0.404316203,0.321096894,0.24630631,0.182824216,0.133094948,0.0990333,0.081950795,
0.082505184,0.100675119,0.135760981,0.186411809,0.250677325,0.326083027,0.409725467,0.498384044,0.588645018,0.677032946,0.760144507,0.834779544,0.898064282,0.947561983,0.981366768,0.998177006,0.99734543,0.978904058,0.943562964,0.892682935,0.828223074,0.752665366,0.668919114,0.580208913,0.489950493,0.401619198,0.318616167,0.244137381,0.181050596,0.131784931,0.098237327,0.081699514,
0.08280827,0.101520904,0.137116896,0.188225647,0.252879245,0.328588246,0.412437522,0.50119851,0.591453524,0.679727354,0.762621071,0.836942904,0.89983114,0.948864306,0.982154412,0.998419644,0.997033718,0.978049999,0.942199443,0.890862454,0.826015728,0.750156149,0.66620464,0.577393702,0.487142944,0.398927412,0.316143791,0.241979611,0.179290517,0.130490313,0.097458018,0.081465522,
0.083128604,0.102383229,0.13848801,0.190052755,0.255091996,0.331101439,0.415154388,0.504014438,0.59426009,0.682416491,0.765089236,0.839095062,0.901584424,0.950151206,0.982925378,0.998644988,0.996704765,0.977179416,0.94082075,0.889028736,0.823797593,0.747639003,0.663485406,0.574577081,0.484337388,0.396240949,0.31367986,0.239833085,0.177544046,0.129211143,0.096695404,0.081248827,
0.083466172,0.103262063,0.13987427,0.191893064,0.257315495,0.333622512,0.417875964,0.506831725,0.597064608,0.685100256,0.76754891,0.841235938,0.903324067,0.951422634,0.983679634,0.998853032,0.996358585,0.97629234,0.939426937,0.887181853,0.821568752,0.745114025,0.660761513,0.571759156,0.481533933,0.393559908,0.311224466,0.237697881,0.175811247,0.127947469,0.095949512,0.081049437,
0.083820962,0.104157371,0.141275624,0.193746505,0.259549657,0.336151371,0.420602148,0.509650262,0.599866974,0.687778547,0.77,0.843365449,0.905050005,0.952678542,0.984417154,0.999043766,0.995995189,0.975388807,0.938018056,0.885321872,0.819329289,0.74258131,0.658033065,0.568940033,0.478732683,0.390884392,0.308777703,0.235574081,0.174092186,0.126699339,0.095220371,0.080867361,
0.084192961,0.105069121,0.142692018,0.195613007,0.261794399,0.33868792,0.423332835,0.512469945,0.602667082,0.690451263,0.772442414,0.845483517,0.906762172,0.953918882,0.985137909,0.999217183,0.995614591,0.974468849,0.93659416,0.883448865,0.81707929,0.740040952,0.655300165,0.566119818,0.475933744,0.388214501,0.306339662,0.233461765,0.172386929,0.1254668,0.094508009,0.080702604,
0.084582154,0.105997278,0.144123401,0.197492501,0.264049635,0.341232062,0.426067923,0.515290666,0.605464826,0.693118304,0.774876059,0.847590061,0.908460503,0.955143608,0.985841872,0.999373277,0.995216807,0.973532502,0.935155304,0.881562902,0.814818838,0.737493048,0.652562915,0.563298618,0.473137222,0.385550335,0.303910435,0.231361013,0.170695539,0.124249899,0.093812452,0.080555174,
0.084988526,0.106941807,0.145569717,0.199384916,0.266315281,0.343783703,0.428807309,0.518112319,0.6082601,0.695779569,0.777300845,0.849685002,0.910144936,0.956352673,0.986529016,0.999512042,0.99480185,0.972579801,0.933701541,0.879664054,0.812548019,0.734937695,0.649821418,0.560476538,0.470343222,0.382891996,0.301490114,0.229271903,0.169018081,0.123048681,0.093133727,0.080425075,
0.085412063,0.107902672,0.147030913,0.201290179,0.268591252,0.346342746,0.43155089,0.520934797,0.611052799,0.698434957,0.779716678,0.851768261,0.911815405,0.957546033,0.987199316,0.999633474,0.994369736,0.971610781,0.932232927,0.877752393,0.810266918,0.732374987,0.647075779,0.557653687,0.46755185,0.380239584,0.29907879,0.227194515,0.167354617,0.121863192,0.092471859,0.080312313,
0.085852749,0.108879837,0.148506932,0.20320822,0.270877461,0.348909094,0.434298561,0.523757995,0.613842817,0.701084369,0.782123469,0.853839759,0.913471848,0.958723641,0.987852746,0.999737566,0.993920483,0.97062548,0.930749516,0.875827991,0.807975622,0.729805023,0.644326101,0.554830169,0.464763211,0.377593198,0.296676555,0.225128927,0.16570521,0.120693476,0.091826873,0.080216891,
0.086310566,0.109873265,0.14999772,0.205138965,0.273173822,0.351482651,0.43705022,0.526581806,0.616630051,0.703727704,0.784521126,0.855899417,0.915114202,0.959885453,0.988489282,0.999824315,0.993454106,0.969623934,0.929251366,0.873890921,0.805674218,0.727227898,0.641572487,0.552006092,0.46197741,0.374952938,0.294283499,0.223075217,0.164069923,0.119539577,0.091198793,0.080138814,
0.086785498,0.110882919,0.15150322,0.207082342,0.275480248,0.354063319,0.439805763,0.529406123,0.619414393,0.706364863,0.786909559,0.857947159,0.916742407,0.961031427,0.989108899,0.999893719,0.992970623,0.968606181,0.927738531,0.871941255,0.803362791,0.724643711,0.638815042,0.549181562,0.459194553,0.372318905,0.291899712,0.221033463,0.162448817,0.11840154,0.090587644,0.080078085,
0.087277527,0.11190876,0.153023375,0.209038279,0.277796653,0.356651001,0.442565085,0.532230839,0.62219574,0.708995746,0.789288678,0.859982907,0.918356399,0.962161517,0.989711575,0.999945774,0.992470053,0.967572261,0.92621107,0.869979067,0.80104143,0.722052558,0.636053869,0.546356686,0.456414743,0.369691197,0.289525284,0.21900374,0.160841954,0.117279407,0.089993448,0.080034705,
0.087786634,0.112950751,0.154558128,0.2110067,0.280122949,0.359245599,0.445328083,0.535055849,0.624973986,0.711620254,0.791658392,0.862006585,0.919956118,0.963275683,0.990297286,0.999980478,0.991952415,0.96652221,0.924669039,0.868004431,0.798710221,0.719454538,0.633289072,0.54353157,0.453638087,0.367069914,0.287160305,0.216986127,0.159249393,0.11617322,0.089416227,0.080008676,
0.088312799,0.114008851,0.156107421,0.212987531,0.282459049,0.361847017,0.448094652,0.537881045,0.627749026,0.714238287,0.794018614,0.864018115,0.921541505,0.964373881,0.990866011,0.999997831,0.991417727,0.96545607,0.923112498,0.866017422,0.796369253,0.716849748,0.630520757,0.540706321,0.450864688,0.364455154,0.284804863,0.214980699,0.157671196,0.115083021,0.088856004,0.08};
#endif /* HAMMING_CONSTANTS_H_ */
