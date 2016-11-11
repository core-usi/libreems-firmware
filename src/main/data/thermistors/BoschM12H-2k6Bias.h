/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2011 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup dataInitialisers
 *
 * Generated by FreeTherm 0.7-SNAPSHOT using the following parameters:
 *
 * Bias Resistor:
 * - Value: 2600
 *
 * Sensor Sample Points:
 * - Temp Low  : 0
 * - Temp Mid  : 30
 * - Temp High : 80
 * - Res Low   : 5896
 * - Res Mid   : 1707
 * - Res High  : 323
 *
 * Temp Units:
 * - Input Temp Scale: Celcius
 * - Output Temp Scale: Kelvin
 *
 * Bosch M12-H datasheet: http://www.bosch-motorsport.de/en-US/literature/en-US/0281002170_DataSheet_enUS_T6821419403.pdf
 */


65535, 64309, 57688, 54397, 52273, 50730, 49533, 48560, 47746, 47049, 46440, 45902, 45421, 44985, 44589, 44225,
43890, 43579, 43289, 43018, 42763, 42523, 42297, 42082, 41878, 41684, 41499, 41322, 41153, 40991, 40835, 40685,
40541, 40402, 40268, 40138, 40013, 39891, 39773, 39659, 39549, 39441, 39336, 39235, 39136, 39039, 38945, 38853,
38764, 38676, 38591, 38508, 38426, 38346, 38268, 38192, 38117, 38043, 37972, 37901, 37832, 37764, 37697, 37632,
37567, 37504, 37442, 37381, 37321, 37262, 37204, 37147, 37091, 37035, 36981, 36927, 36874, 36822, 36770, 36720,
36670, 36620, 36572, 36524, 36476, 36430, 36383, 36338, 36293, 36249, 36205, 36161, 36118, 36076, 36034, 35993,
35952, 35912, 35872, 35832, 35793, 35754, 35716, 35678, 35641, 35604, 35567, 35531, 35495, 35459, 35424, 35389,
35355, 35320, 35286, 35253, 35219, 35186, 35154, 35121, 35089, 35057, 35026, 34995, 34964, 34933, 34902, 34872,
34842, 34812, 34783, 34754, 34724, 34696, 34667, 34639, 34611, 34583, 34555, 34527, 34500, 34473, 34446, 34419,
34393, 34366, 34340, 34314, 34289, 34263, 34238, 34212, 34187, 34162, 34138, 34113, 34089, 34064, 34040, 34016,
33992, 33969, 33945, 33922, 33899, 33875, 33853, 33830, 33807, 33785, 33762, 33740, 33718, 33696, 33674, 33652,
33630, 33609, 33587, 33566, 33545, 33524, 33503, 33482, 33461, 33441, 33420, 33400, 33380, 33360, 33339, 33319,
33300, 33280, 33260, 33241, 33221, 33202, 33182, 33163, 33144, 33125, 33106, 33087, 33069, 33050, 33031, 33013,
32994, 32976, 32958, 32940, 32922, 32904, 32886, 32868, 32850, 32832, 32815, 32797, 32780, 32763, 32745, 32728,
32711, 32694, 32677, 32660, 32643, 32626, 32609, 32593, 32576, 32559, 32543, 32526, 32510, 32494, 32477, 32461,
32445, 32429, 32413, 32397, 32381, 32365, 32350, 32334, 32318, 32303, 32287, 32272, 32256, 32241, 32226, 32210,
32195, 32180, 32165, 32150, 32135, 32120, 32105, 32090, 32075, 32060, 32046, 32031, 32016, 32002, 31987, 31973,
31958, 31944, 31929, 31915, 31901, 31887, 31872, 31858, 31844, 31830, 31816, 31802, 31788, 31774, 31760, 31747,
31733, 31719, 31705, 31692, 31678, 31665, 31651, 31637, 31624, 31611, 31597, 31584, 31570, 31557, 31544, 31531,
31518, 31504, 31491, 31478, 31465, 31452, 31439, 31426, 31413, 31400, 31388, 31375, 31362, 31349, 31336, 31324,
31311, 31298, 31286, 31273, 31261, 31248, 31236, 31223, 31211, 31198, 31186, 31174, 31161, 31149, 31137, 31125,
31112, 31100, 31088, 31076, 31064, 31052, 31040, 31028, 31016, 31004, 30992, 30980, 30968, 30956, 30944, 30932,
30920, 30909, 30897, 30885, 30873, 30862, 30850, 30838, 30827, 30815, 30804, 30792, 30780, 30769, 30757, 30746,
30735, 30723, 30712, 30700, 30689, 30678, 30666, 30655, 30644, 30632, 30621, 30610, 30599, 30587, 30576, 30565,
30554, 30543, 30532, 30521, 30510, 30499, 30488, 30477, 30466, 30455, 30444, 30433, 30422, 30411, 30400, 30389,
30378, 30367, 30356, 30346, 30335, 30324, 30313, 30303, 30292, 30281, 30270, 30260, 30249, 30238, 30228, 30217,
30206, 30196, 30185, 30175, 30164, 30154, 30143, 30133, 30122, 30112, 30101, 30091, 30080, 30070, 30059, 30049,
30038, 30028, 30018, 30007, 29997, 29987, 29976, 29966, 29956, 29945, 29935, 29925, 29915, 29904, 29894, 29884,
29874, 29863, 29853, 29843, 29833, 29823, 29813, 29802, 29792, 29782, 29772, 29762, 29752, 29742, 29732, 29722,
29712, 29702, 29692, 29682, 29671, 29661, 29651, 29641, 29632, 29622, 29612, 29602, 29592, 29582, 29572, 29562,
29552, 29542, 29532, 29522, 29512, 29503, 29493, 29483, 29473, 29463, 29453, 29443, 29434, 29424, 29414, 29404,
29394, 29385, 29375, 29365, 29355, 29345, 29336, 29326, 29316, 29306, 29297, 29287, 29277, 29268, 29258, 29248,
29238, 29229, 29219, 29209, 29200, 29190, 29180, 29171, 29161, 29151, 29142, 29132, 29122, 29113, 29103, 29093,
29084, 29074, 29065, 29055, 29045, 29036, 29026, 29017, 29007, 28997, 28988, 28978, 28969, 28959, 28949, 28940,
28930, 28921, 28911, 28902, 28892, 28883, 28873, 28863, 28854, 28844, 28835, 28825, 28816, 28806, 28797, 28787,
28778, 28768, 28758, 28749, 28739, 28730, 28720, 28711, 28701, 28692, 28682, 28673, 28663, 28654, 28644, 28635,
28625, 28616, 28606, 28597, 28587, 28578, 28568, 28559, 28549, 28540, 28530, 28520, 28511, 28501, 28492, 28482,
28473, 28463, 28454, 28444, 28435, 28425, 28416, 28406, 28397, 28387, 28378, 28368, 28359, 28349, 28340, 28330,
28320, 28311, 28301, 28292, 28282, 28273, 28263, 28254, 28244, 28234, 28225, 28215, 28206, 28196, 28187, 28177,
28167, 28158, 28148, 28139, 28129, 28120, 28110, 28100, 28091, 28081, 28071, 28062, 28052, 28043, 28033, 28023,
28014, 28004, 27994, 27985, 27975, 27965, 27956, 27946, 27936, 27927, 27917, 27907, 27898, 27888, 27878, 27868,
27859, 27849, 27839, 27829, 27820, 27810, 27800, 27790, 27781, 27771, 27761, 27751, 27741, 27732, 27722, 27712,
27702, 27692, 27682, 27672, 27663, 27653, 27643, 27633, 27623, 27613, 27603, 27593, 27583, 27573, 27563, 27553,
27543, 27533, 27523, 27513, 27503, 27493, 27483, 27473, 27463, 27453, 27443, 27433, 27423, 27413, 27403, 27393,
27383, 27372, 27362, 27352, 27342, 27332, 27321, 27311, 27301, 27291, 27280, 27270, 27260, 27250, 27239, 27229,
27219, 27208, 27198, 27188, 27177, 27167, 27156, 27146, 27135, 27125, 27115, 27104, 27094, 27083, 27072, 27062,
27051, 27041, 27030, 27020, 27009, 26998, 26988, 26977, 26966, 26956, 26945, 26934, 26923, 26913, 26902, 26891,
26880, 26869, 26858, 26847, 26837, 26826, 26815, 26804, 26793, 26782, 26771, 26760, 26748, 26737, 26726, 26715,
26704, 26693, 26682, 26670, 26659, 26648, 26637, 26625, 26614, 26603, 26591, 26580, 26568, 26557, 26545, 26534,
26522, 26511, 26499, 26488, 26476, 26464, 26453, 26441, 26429, 26417, 26406, 26394, 26382, 26370, 26358, 26346,
26334, 26322, 26310, 26298, 26286, 26274, 26262, 26250, 26237, 26225, 26213, 26201, 26188, 26176, 26163, 26151,
26138, 26126, 26113, 26101, 26088, 26075, 26063, 26050, 26037, 26024, 26012, 25999, 25986, 25973, 25960, 25947,
25934, 25920, 25907, 25894, 25881, 25867, 25854, 25841, 25827, 25814, 25800, 25786, 25773, 25759, 25745, 25732,
25718, 25704, 25690, 25676, 25662, 25648, 25634, 25619, 25605, 25591, 25576, 25562, 25548, 25533, 25518, 25504,
25489, 25474, 25459, 25444, 25429, 25414, 25399, 25384, 25369, 25354, 25338, 25323, 25307, 25292, 25276, 25260,
25244, 25228, 25212, 25196, 25180, 25164, 25148, 25131, 25115, 25098, 25082, 25065, 25048, 25031, 25014, 24997,
24980, 24963, 24945, 24928, 24910, 24892, 24875, 24857, 24839, 24821, 24802, 24784, 24766, 24747, 24728, 24709,
24690, 24671, 24652, 24633, 24613, 24594, 24574, 24554, 24534, 24514, 24494, 24473, 24452, 24432, 24411, 24390,
24368, 24347, 24325, 24303, 24281, 24259, 24237, 24214, 24192, 24169, 24145, 24122, 24098, 24075, 24051, 24026,
24002, 23977, 23952, 23927, 23901, 23875, 23849, 23823, 23796, 23769, 23742, 23715, 23687, 23659, 23630, 23601,
23572, 23542, 23512, 23482, 23451, 23420, 23388, 23356, 23323, 23290, 23256, 23222, 23188, 23152, 23117, 23080,
23043, 23006, 22967, 22928, 22888, 22848, 22806, 22764, 22721, 22677, 22632, 22586, 22539, 22491, 22442, 22391,
22339, 22286, 22231, 22175, 22116, 22056, 21995, 21931, 21864, 21796, 21724, 21650, 21573, 21492, 21407, 21318,
21225, 21126, 21021, 20909, 20790, 20661, 20521, 20369, 20200, 20012, 19797, 19548, 19250, 18874, 18363, 17532
