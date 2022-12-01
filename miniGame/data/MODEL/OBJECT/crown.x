xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 234;
 -70.88987;59.98564;-0.10367;,
 -67.36245;59.98564;-22.37482;,
 -67.36245;0.66150;-22.37482;,
 -70.88987;0.66150;-0.10367;,
 -53.65374;59.98564;-17.92059;,
 -56.47567;59.98564;-0.10367;,
 -56.47567;0.66150;-0.10367;,
 -53.65374;0.66150;-17.92059;,
 -57.00994;59.95625;-42.30177;,
 -57.12548;0.66150;-42.46592;,
 -45.46418;59.98564;-33.99349;,
 -45.46418;0.66150;-33.99349;,
 -41.18115;59.98564;-58.41025;,
 -41.06559;0.63212;-58.24613;,
 -32.70872;59.98564;-46.74893;,
 -32.70872;0.66150;-46.74893;,
 -21.09006;59.98564;-68.64723;,
 -21.09006;0.66150;-68.64723;,
 -16.63582;59.98564;-54.93852;,
 -16.63582;0.66150;-54.93852;,
 1.18110;59.98564;-72.17465;,
 1.18110;0.66150;-72.17465;,
 1.18110;59.98564;-57.76041;,
 1.18110;0.66150;-57.76041;,
 23.45226;59.98564;-68.64723;,
 23.45226;0.66150;-68.64723;,
 18.99801;59.98564;-54.93852;,
 18.99801;0.66150;-54.93852;,
 43.54334;59.98564;-58.41025;,
 43.54334;0.66150;-58.41025;,
 35.07091;59.98564;-46.74893;,
 35.07091;0.66150;-46.74893;,
 59.48770;59.98564;-42.46593;,
 59.48770;0.66150;-42.46593;,
 47.82639;59.98564;-33.99350;,
 47.82639;0.66150;-33.99350;,
 69.72467;59.98564;-22.37481;,
 69.72467;0.66150;-22.37481;,
 56.01594;59.98564;-17.92057;,
 56.01594;0.66150;-17.92057;,
 73.25206;59.98564;-0.10365;,
 73.25206;0.66150;-0.10365;,
 58.83787;59.98564;-0.10366;,
 58.83787;0.66150;-0.10366;,
 69.72466;59.98564;22.16752;,
 69.72466;0.66150;22.16752;,
 56.01591;59.98564;17.71325;,
 56.01591;0.66150;17.71325;,
 59.48769;59.98564;42.25860;,
 59.48769;0.66150;42.25860;,
 47.82638;59.98564;33.78615;,
 47.82638;0.66150;33.78615;,
 43.54330;59.98564;58.20296;,
 43.54330;0.66150;58.20296;,
 35.07083;59.98564;46.54167;,
 35.07083;0.66150;46.54167;,
 23.45219;59.98564;68.43990;,
 23.45219;0.66150;68.43990;,
 18.99798;59.98564;54.73119;,
 18.99798;0.66150;54.73119;,
 1.18104;59.98564;71.96731;,
 1.18104;0.66150;71.96731;,
 1.18104;59.98564;57.55308;,
 1.18104;0.66150;57.55308;,
 -21.09012;59.98564;68.43984;,
 -21.09012;0.66150;68.43984;,
 -16.63588;59.98564;54.73116;,
 -16.63588;0.66150;54.73116;,
 -41.18121;59.98564;58.20290;,
 -41.18121;0.66150;58.20290;,
 -32.70873;59.98564;46.54159;,
 -32.70873;0.66150;46.54159;,
 -57.12553;59.98564;42.25851;,
 -57.12553;0.66150;42.25851;,
 -45.46423;59.98564;33.78606;,
 -45.46423;0.66150;33.78606;,
 -67.36245;59.98564;22.16738;,
 -67.36245;0.66150;22.16738;,
 -53.65376;59.98564;17.71316;,
 -53.65376;0.66150;17.71316;,
 -70.88987;59.98564;-0.10367;,
 -70.88987;0.66150;-0.10367;,
 -56.47567;59.98564;-0.10367;,
 -56.47567;0.66150;-0.10367;,
 -70.88987;0.66150;-0.10367;,
 -67.36245;0.66150;-22.37482;,
 -53.65374;0.66150;-17.92059;,
 -56.47567;0.66150;-0.10367;,
 -57.12548;0.66150;-42.46592;,
 -45.46418;0.66150;-33.99349;,
 -41.06559;0.63212;-58.24613;,
 -32.70872;0.66150;-46.74893;,
 -21.09006;0.66150;-68.64723;,
 -16.63582;0.66150;-54.93852;,
 1.18110;0.66150;-72.17465;,
 1.18110;0.66150;-57.76041;,
 23.45226;0.66150;-68.64723;,
 18.99801;0.66150;-54.93852;,
 43.54334;0.66150;-58.41025;,
 35.07091;0.66150;-46.74893;,
 59.48770;0.66150;-42.46593;,
 47.82639;0.66150;-33.99350;,
 69.72467;0.66150;-22.37481;,
 56.01594;0.66150;-17.92057;,
 73.25206;0.66150;-0.10365;,
 58.83787;0.66150;-0.10366;,
 69.72466;0.66150;22.16752;,
 56.01591;0.66150;17.71325;,
 59.48769;0.66150;42.25860;,
 47.82638;0.66150;33.78615;,
 43.54330;0.66150;58.20296;,
 35.07083;0.66150;46.54167;,
 23.45219;0.66150;68.43990;,
 18.99798;0.66150;54.73119;,
 1.18104;0.66150;71.96731;,
 1.18104;0.66150;57.55308;,
 -21.09012;0.66150;68.43984;,
 -16.63588;0.66150;54.73116;,
 -41.18121;0.66150;58.20290;,
 -32.70873;0.66150;46.54159;,
 -57.12553;0.66150;42.25851;,
 -45.46423;0.66150;33.78606;,
 -67.36245;0.66150;22.16738;,
 -53.65376;0.66150;17.71316;,
 1.18104;122.67872;-72.70165;,
 1.18110;59.98564;-72.17465;,
 -21.09006;59.98564;-68.64723;,
 23.45226;59.98564;-68.64723;,
 -16.63582;59.98564;-54.93852;,
 1.18110;59.98564;-57.76041;,
 18.99801;59.98564;-54.93852;,
 -42.36621;122.70702;-58.70295;,
 -41.18115;59.98564;-58.41025;,
 -57.00994;59.95625;-42.30177;,
 -45.46418;59.98564;-33.99349;,
 -32.70872;59.98564;-46.74893;,
 -66.73427;122.72714;-24.33493;,
 -67.36245;59.98564;-22.37482;,
 -53.65374;59.98564;-17.92059;,
 -66.73506;122.71178;24.12291;,
 -67.36245;59.98564;22.16738;,
 -57.12553;59.98564;42.25851;,
 -45.46423;59.98564;33.78606;,
 -53.65376;59.98564;17.71316;,
 -42.36484;122.71879;58.49485;,
 -41.18121;59.98564;58.20290;,
 -21.09012;59.98564;68.43984;,
 -16.63588;59.98564;54.73116;,
 -32.70873;59.98564;46.54159;,
 1.18096;122.69171;72.49536;,
 1.18104;59.98564;71.96731;,
 23.45219;59.98564;68.43990;,
 18.99798;59.98564;54.73119;,
 1.18104;59.98564;57.55308;,
 44.72843;122.71903;58.49553;,
 43.54330;59.98564;58.20296;,
 59.48769;59.98564;42.25860;,
 47.82638;59.98564;33.78615;,
 35.07083;59.98564;46.54167;,
 69.09578;122.71100;24.13037;,
 69.72466;59.98564;22.16752;,
 73.25206;59.98564;-0.10365;,
 58.83787;59.98564;-0.10366;,
 56.01591;59.98564;17.71325;,
 69.09814;122.75343;-24.32480;,
 69.72467;59.98564;-22.37481;,
 59.48770;59.98564;-42.46593;,
 47.82639;59.98564;-33.99350;,
 56.01594;59.98564;-17.92057;,
 44.72338;122.69948;-58.70109;,
 43.54334;59.98564;-58.41025;,
 35.07091;59.98564;-46.74893;,
 13.69729;34.38433;-69.84096;,
 1.18109;34.38433;-78.69415;,
 1.18110;54.18825;-72.14145;,
 13.69729;34.38433;-69.84096;,
 1.18110;14.58045;-72.14145;,
 -11.33510;34.38433;-69.91514;,
 -11.33510;34.38433;-69.91514;,
 -11.33509;34.38433;69.68627;,
 1.18110;14.58045;71.81009;,
 1.18110;34.38433;77.42472;,
 -11.33509;34.38433;69.68627;,
 1.18110;54.18825;71.81009;,
 1.18110;54.18825;71.81009;,
 13.69730;34.38433;69.62214;,
 13.69730;34.38433;69.62214;,
 -68.50069;34.38433;-13.72552;,
 -70.81273;14.58045;-0.63471;,
 -77.46422;34.38433;-0.63470;,
 -68.50069;34.38433;-13.72552;,
 -70.81273;54.18825;-0.63471;,
 -68.75900;34.38433;12.45610;,
 -68.75900;34.38433;12.45610;,
 70.98384;34.38433;12.45609;,
 73.16230;14.58045;-0.63473;,
 78.86152;34.38433;-0.63473;,
 70.98384;34.38433;12.45609;,
 73.16230;54.18825;-0.63473;,
 73.16230;54.18825;-0.63473;,
 70.84034;34.38433;-13.72554;,
 70.84034;34.38433;-13.72554;,
 -43.37702;34.36144;-56.04514;,
 -53.38518;34.36144;-55.30393;,
 -48.75172;41.96237;-50.67043;,
 -43.37702;34.36144;-56.04514;,
 -48.75172;26.76053;-50.67043;,
 -48.75172;26.76053;-50.67043;,
 -54.12635;34.36144;-45.29578;,
 -54.12635;34.36144;-45.29578;,
 46.42869;34.36956;55.34261;,
 51.80333;26.76864;49.96792;,
 55.77349;34.36956;53.93806;,
 46.42869;34.36956;55.34261;,
 51.80333;41.97048;49.96792;,
 57.17802;34.36956;44.59323;,
 51.80333;41.97048;49.96792;,
 57.17802;34.36956;44.59323;,
 -54.32733;34.33862;44.98745;,
 -49.14713;26.78413;50.34132;,
 -53.78059;34.38506;54.97479;,
 -49.14713;41.98597;50.34132;,
 -54.32733;34.33862;44.98745;,
 -49.14713;41.98597;50.34132;,
 -43.57799;34.33862;55.73674;,
 -43.57799;34.33862;55.73674;,
 57.00182;34.38433;-44.96716;,
 51.62717;26.78342;-50.34181;,
 55.59729;34.38433;-54.31197;,
 51.62717;41.98528;-50.34181;,
 57.00182;34.38433;-44.96716;,
 51.62717;41.98528;-50.34181;,
 46.25249;34.38433;-55.71650;,
 46.25249;34.38433;-55.71650;;
 
 152;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;1,8,9,2;,
 4;10,4,7,11;,
 4;8,12,13,9;,
 4;14,10,11,15;,
 4;12,16,17,13;,
 4;18,14,15,19;,
 4;16,20,21,17;,
 4;22,18,19,23;,
 4;20,24,25,21;,
 4;26,22,23,27;,
 4;24,28,29,25;,
 4;30,26,27,31;,
 4;28,32,33,29;,
 4;34,30,31,35;,
 4;32,36,37,33;,
 4;38,34,35,39;,
 4;36,40,41,37;,
 4;42,38,39,43;,
 4;40,44,45,41;,
 4;46,42,43,47;,
 4;44,48,49,45;,
 4;50,46,47,51;,
 4;48,52,53,49;,
 4;54,50,51,55;,
 4;52,56,57,53;,
 4;58,54,55,59;,
 4;56,60,61,57;,
 4;62,58,59,63;,
 4;60,64,65,61;,
 4;66,62,63,67;,
 4;64,68,69,65;,
 4;70,66,67,71;,
 4;68,72,73,69;,
 4;74,70,71,75;,
 4;72,76,77,73;,
 4;78,74,75,79;,
 4;76,80,81,77;,
 4;82,78,79,83;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,84,87,123;,
 3;124,125,126;,
 3;124,127,125;,
 3;124,126,128;,
 3;124,128,129;,
 3;124,129,130;,
 3;124,130,127;,
 3;131,132,133;,
 3;131,126,132;,
 3;131,133,134;,
 3;131,134,135;,
 3;131,135,128;,
 3;131,128,126;,
 3;136,137,0;,
 3;136,133,137;,
 3;136,0,5;,
 3;136,5,138;,
 3;136,138,134;,
 3;136,134,133;,
 3;139,140,141;,
 3;139,0,140;,
 3;139,5,0;,
 3;139,141,142;,
 3;139,142,143;,
 3;139,143,5;,
 3;144,145,146;,
 3;144,141,145;,
 3;144,146,147;,
 3;144,147,148;,
 3;144,148,142;,
 3;144,142,141;,
 3;149,150,151;,
 3;149,146,150;,
 3;149,151,152;,
 3;149,152,153;,
 3;149,153,147;,
 3;149,147,146;,
 3;154,155,156;,
 3;154,151,155;,
 3;154,156,157;,
 3;154,157,158;,
 3;154,158,152;,
 3;154,152,151;,
 3;159,160,161;,
 3;159,156,160;,
 3;159,161,162;,
 3;159,162,163;,
 3;159,163,157;,
 3;159,157,156;,
 3;164,165,166;,
 3;164,161,165;,
 3;164,166,167;,
 3;164,167,168;,
 3;164,168,162;,
 3;164,162,161;,
 3;169,170,127;,
 3;169,166,170;,
 3;169,127,130;,
 3;169,130,171;,
 3;169,171,167;,
 3;169,167,166;,
 3;172,173,174;,
 3;175,176,173;,
 3;177,173,176;,
 3;178,174,173;,
 3;179,180,181;,
 3;182,181,183;,
 3;184,181,185;,
 3;186,181,180;,
 3;187,188,189;,
 3;190,189,191;,
 3;192,191,189;,
 3;193,189,188;,
 3;194,195,196;,
 3;197,196,198;,
 3;199,196,200;,
 3;201,196,195;,
 3;202,203,204;,
 3;205,206,203;,
 3;207,208,203;,
 3;209,204,203;,
 3;210,211,212;,
 3;213,212,214;,
 3;215,212,211;,
 3;216,212,217;,
 3;218,219,220;,
 3;221,222,220;,
 3;223,220,224;,
 3;225,220,219;,
 3;226,227,228;,
 3;229,230,228;,
 3;231,228,232;,
 3;233,228,227;;
 
 MeshMaterialList {
  3;
  152;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.000000;0.021600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.081600;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.611765;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  164;
  -0.999997;0.002532;0.000000;,
  -0.950137;0.000248;-0.311833;,
  -0.808550;-0.005253;-0.588405;,
  -0.590419;-0.007888;-0.807058;,
  -0.310060;-0.005750;-0.950700;,
  0.000000;-0.004203;-0.999991;,
  0.309013;-0.005309;-0.951043;,
  0.587768;-0.007405;-0.808996;,
  0.809007;-0.005516;-0.587773;,
  0.951056;-0.000053;-0.309017;,
  0.999997;0.002533;0.000000;,
  0.951056;-0.000067;0.309018;,
  0.809007;-0.005550;0.587773;,
  0.587767;-0.007438;0.808996;,
  0.309011;-0.005328;0.951044;,
  -0.000001;-0.004210;0.999991;,
  -0.309013;-0.005323;0.951043;,
  -0.587768;-0.007427;0.808995;,
  -0.809008;-0.005536;0.587771;,
  -0.951056;-0.000061;0.309017;,
  -1.000000;0.000000;0.000000;,
  -0.950444;0.000758;-0.310896;,
  -0.807851;0.000756;-0.589387;,
  -0.589565;-0.000850;-0.807721;,
  -0.311114;-0.000849;-0.950372;,
  0.000000;0.000000;-1.000000;,
  0.309019;0.000000;-0.951056;,
  0.587786;0.000000;-0.809017;,
  0.809016;0.000000;-0.587786;,
  0.951056;0.000000;-0.309017;,
  1.000000;0.000000;0.000000;,
  0.951056;0.000000;0.309018;,
  0.809016;0.000000;0.587786;,
  0.587785;0.000000;0.809017;,
  0.309017;0.000000;0.951056;,
  -0.000001;0.000000;1.000000;,
  -0.309019;0.000000;0.951056;,
  -0.587786;0.000000;0.809016;,
  -0.809018;0.000000;0.587784;,
  -0.951056;0.000000;0.309017;,
  0.993896;0.110324;0.000001;,
  0.945017;0.112764;0.306965;,
  0.803429;0.117946;0.583602;,
  0.583528;0.119742;0.803216;,
  0.306830;0.117781;0.944448;,
  -0.000000;0.116751;0.993161;,
  -0.306831;0.117773;0.944449;,
  -0.583530;0.119723;0.803218;,
  -0.803433;0.117899;0.583605;,
  -0.945023;0.112707;0.306967;,
  -0.993898;0.110301;0.000000;,
  -0.945014;0.112794;-0.306963;,
  -0.803428;0.117951;-0.583602;,
  -0.583529;0.119720;-0.803219;,
  -0.306830;0.117762;-0.944451;,
  0.000001;0.116736;-0.993163;,
  0.306832;0.117758;-0.944451;,
  0.583532;0.119710;-0.803219;,
  0.803430;0.117937;-0.583602;,
  0.945015;0.112786;-0.306963;,
  1.000000;0.000000;0.000000;,
  0.951056;0.000000;0.309017;,
  0.809017;0.000000;0.587786;,
  0.587786;0.000000;0.809017;,
  0.309017;0.000000;0.951056;,
  -0.000000;0.000000;1.000000;,
  -0.309017;0.000000;0.951056;,
  -0.587785;0.000000;0.809017;,
  -0.809017;0.000000;0.587786;,
  -0.951057;0.000000;0.309017;,
  -1.000000;0.000000;-0.000001;,
  -0.951056;0.000000;-0.309018;,
  -0.809017;0.000000;-0.587785;,
  -0.587785;0.000000;-0.809017;,
  -0.309016;0.000000;-0.951057;,
  0.000001;0.000000;-1.000000;,
  0.309018;0.000000;-0.951056;,
  0.587787;0.000000;-0.809016;,
  0.809018;0.000000;-0.587784;,
  0.951057;0.000000;-0.309017;,
  0.000000;-0.008406;-0.999965;,
  -0.591244;-0.014934;-0.806354;,
  -0.949829;-0.000261;-0.312770;,
  -0.951056;-0.000121;0.309017;,
  -0.587718;-0.014854;0.808930;,
  -0.000001;-0.008421;0.999964;,
  0.587716;-0.014875;0.808930;,
  0.951056;-0.000135;0.309018;,
  0.951056;-0.000107;-0.309017;,
  0.587718;-0.014810;-0.808931;,
  0.000000;-1.000000;0.000000;,
  0.000176;-1.000000;0.000638;,
  0.000728;-0.999999;0.001002;,
  0.000552;-1.000000;0.000364;,
  -0.895452;0.336917;0.290951;,
  -0.000000;0.231831;0.972756;,
  0.895452;0.336918;0.290951;,
  -0.552109;0.329074;0.766085;,
  0.570886;0.237681;0.785873;,
  0.891492;0.348334;-0.289664;,
  0.000000;0.360273;0.932847;,
  0.926937;0.224023;0.301001;,
  0.555324;0.307228;-0.772804;,
  0.000000;0.360289;-0.932841;,
  0.559177;0.308185;0.769638;,
  0.926928;0.224065;-0.300997;,
  0.891517;0.348262;0.289673;,
  0.570896;0.237618;-0.785885;,
  -0.555186;0.328405;-0.764146;,
  0.895472;0.336861;-0.290955;,
  0.000001;0.231801;-0.972763;,
  -0.895472;0.336859;-0.290958;,
  0.555187;0.328399;-0.764148;,
  -0.570891;0.237637;-0.785883;,
  -0.891513;0.348277;0.289669;,
  0.000001;0.360389;-0.932802;,
  -0.926924;0.224081;-0.300996;,
  -0.559193;0.308095;0.769662;,
  -0.559197;0.308069;-0.769670;,
  -0.926961;0.223911;0.301009;,
  -0.000001;0.360011;0.932948;,
  -0.891498;0.348316;-0.289667;,
  -0.570891;0.237643;0.785881;,
  0.555163;0.328511;0.764117;,
  -0.511226;0.234423;0.826858;,
  -0.525880;-0.000000;0.850559;,
  0.557494;0.260784;-0.788157;,
  0.577476;-0.000000;-0.816407;,
  -0.574238;-0.000000;-0.818688;,
  0.557494;-0.260785;-0.788157;,
  0.529021;-0.000000;0.848609;,
  -0.511226;-0.234424;0.826858;,
  -0.554262;-0.261464;-0.790209;,
  -0.554262;0.261464;-0.790209;,
  0.514345;0.233915;0.825066;,
  0.514345;-0.233916;0.825065;,
  0.831905;0.239408;0.500617;,
  0.856823;-0.000000;0.515611;,
  -0.825112;-0.000000;-0.564970;,
  -0.795143;0.267062;-0.544449;,
  -0.795143;-0.267063;-0.544449;,
  -0.832695;-0.000000;0.553732;,
  0.852666;-0.000000;-0.522457;,
  0.831905;-0.239408;0.500617;,
  -0.801923;0.269340;0.533269;,
  -0.801923;-0.269340;0.533269;,
  0.828099;0.238312;-0.507404;,
  0.828099;-0.238313;-0.507404;,
  0.127780;0.510797;0.850152;,
  0.127780;-0.510797;0.850152;,
  -0.061842;0.546727;-0.835024;,
  -0.835027;-0.546723;-0.061839;,
  -0.061842;-0.546727;-0.835024;,
  0.850152;-0.510798;0.127778;,
  -0.835027;0.546722;-0.061839;,
  0.850152;0.510798;0.127778;,
  0.850155;0.510793;-0.127779;,
  -0.839451;-0.541270;0.048471;,
  -0.841035;0.539227;0.043534;,
  -0.059924;0.545950;0.835672;,
  0.127778;0.510796;-0.850153;,
  0.850153;-0.510795;-0.127778;,
  -0.064780;-0.547907;0.834027;,
  0.127778;-0.510798;-0.850152;;
  152;
  4;0,1,21,20;,
  4;41,40,60,61;,
  4;1,2,22,21;,
  4;42,41,61,62;,
  4;2,3,23,22;,
  4;43,42,62,63;,
  4;3,4,24,23;,
  4;44,43,63,64;,
  4;4,5,25,24;,
  4;45,44,64,65;,
  4;5,6,26,25;,
  4;46,45,65,66;,
  4;6,7,27,26;,
  4;47,46,66,67;,
  4;7,8,28,27;,
  4;48,47,67,68;,
  4;8,9,29,28;,
  4;49,48,68,69;,
  4;9,10,30,29;,
  4;50,49,69,70;,
  4;10,11,31,30;,
  4;51,50,70,71;,
  4;11,12,32,31;,
  4;52,51,71,72;,
  4;12,13,33,32;,
  4;53,52,72,73;,
  4;13,14,34,33;,
  4;54,53,73,74;,
  4;14,15,35,34;,
  4;55,54,74,75;,
  4;15,16,36,35;,
  4;56,55,75,76;,
  4;16,17,37,36;,
  4;57,56,76,77;,
  4;17,18,38,37;,
  4;58,57,77,78;,
  4;18,19,39,38;,
  4;59,58,78,79;,
  4;19,0,20,39;,
  4;40,59,79,60;,
  4;90,90,90,90;,
  4;90,91,91,90;,
  4;91,92,92,91;,
  4;92,93,93,92;,
  4;93,90,90,93;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  4;90,90,90,90;,
  3;80,5,4;,
  3;80,6,5;,
  3;94,94,94;,
  3;95,44,45;,
  3;95,45,46;,
  3;96,96,96;,
  3;81,3,2;,
  3;81,4,3;,
  3;97,97,97;,
  3;98,42,43;,
  3;98,43,44;,
  3;99,99,99;,
  3;82,1,0;,
  3;82,2,1;,
  3;100,100,100;,
  3;101,40,41;,
  3;101,41,42;,
  3;102,102,102;,
  3;83,19,18;,
  3;83,0,19;,
  3;103,103,103;,
  3;104,104,104;,
  3;105,58,59;,
  3;105,59,40;,
  3;84,17,16;,
  3;84,18,17;,
  3;106,106,106;,
  3;107,56,57;,
  3;107,57,58;,
  3;108,108,108;,
  3;85,15,14;,
  3;85,16,15;,
  3;109,109,109;,
  3;110,54,55;,
  3;110,55,56;,
  3;111,111,111;,
  3;86,13,12;,
  3;86,14,13;,
  3;112,112,112;,
  3;113,52,53;,
  3;113,53,54;,
  3;114,114,114;,
  3;87,11,10;,
  3;87,12,11;,
  3;115,115,115;,
  3;116,50,51;,
  3;116,51,52;,
  3;117,117,117;,
  3;88,9,8;,
  3;88,10,9;,
  3;118,118,118;,
  3;119,48,49;,
  3;119,49,50;,
  3;120,120,120;,
  3;89,7,6;,
  3;89,8,7;,
  3;121,121,121;,
  3;122,46,47;,
  3;122,47,48;,
  3;123,123,123;,
  3;127,127,126;,
  3;127,129,127;,
  3;128,128,132;,
  3;128,133,128;,
  3;125,131,125;,
  3;125,125,124;,
  3;134,130,130;,
  3;130,130,135;,
  3;138,140,138;,
  3;138,138,139;,
  3;141,144,141;,
  3;141,141,145;,
  3;137,143,137;,
  3;137,137,136;,
  3;146,142,142;,
  3;142,142,147;,
  3;150,150,150;,
  3;152,152,152;,
  3;151,151,151;,
  3;154,154,154;,
  3;149,149,149;,
  3;148,148,148;,
  3;153,153,153;,
  3;155,155,155;,
  3;157,157,157;,
  3;158,158,158;,
  3;159,159,159;,
  3;162,162,162;,
  3;161,161,161;,
  3;156,156,156;,
  3;160,160,160;,
  3;163,163,163;;
 }
 MeshTextureCoords {
  234;
  0.000000;0.000000;,
  0.050000;0.000000;,
  0.050000;1.000000;,
  0.000000;1.000000;,
  0.050000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.050000;1.000000;,
  0.100000;0.000000;,
  0.100000;1.000000;,
  0.100000;0.000000;,
  0.100000;1.000000;,
  0.150000;0.000000;,
  0.150000;1.000000;,
  0.150000;0.000000;,
  0.150000;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.300000;0.000000;,
  0.300000;1.000000;,
  0.300000;0.000000;,
  0.300000;1.000000;,
  0.350000;0.000000;,
  0.350000;1.000000;,
  0.350000;0.000000;,
  0.350000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.450000;0.000000;,
  0.450000;1.000000;,
  0.450000;0.000000;,
  0.450000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.550000;0.000000;,
  0.550000;1.000000;,
  0.550000;0.000000;,
  0.550000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.650000;0.000000;,
  0.650000;1.000000;,
  0.650000;0.000000;,
  0.650000;1.000000;,
  0.700000;0.000000;,
  0.700000;1.000000;,
  0.700000;0.000000;,
  0.700000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.850000;0.000000;,
  0.850000;1.000000;,
  0.850000;0.000000;,
  0.850000;1.000000;,
  0.900000;0.000000;,
  0.900000;1.000000;,
  0.900000;0.000000;,
  0.900000;1.000000;,
  0.950000;0.000000;,
  0.950000;1.000000;,
  0.950000;0.000000;,
  0.950000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.750000;1.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;1.000000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  0.500000;0.000000;,
  0.250000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  0.250000;0.000000;,
  0.000000;0.500000;,
  0.250000;1.000000;,
  0.750000;1.000000;,
  0.250000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;1.000000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  0.500000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;1.000000;,
  1.000000;0.500000;,
  0.250000;0.000000;,
  1.000000;0.250000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.000000;0.750000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.250000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  1.000000;0.250000;,
  0.500000;0.000000;,
  0.250000;0.000000;;
 }
}
