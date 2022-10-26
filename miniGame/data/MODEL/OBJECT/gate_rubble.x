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
 116;
 -475.67188;630.92184;-116.20662;,
 474.18643;695.81022;-116.20662;,
 425.95655;569.81871;-94.26550;,
 -477.38546;500.01314;-94.26550;,
 474.18643;695.81022;-116.20662;,
 474.18643;695.81022;130.73266;,
 425.95655;569.81871;79.95587;,
 425.95655;569.81871;-94.26550;,
 474.18643;695.81022;130.73266;,
 -475.67188;630.92184;130.73266;,
 -477.38546;500.01314;79.95587;,
 425.95655;569.81871;79.95587;,
 -475.67188;630.92184;130.73266;,
 -475.67188;630.92184;-116.20662;,
 -477.38546;500.01314;-94.26550;,
 -477.38546;500.01314;79.95587;,
 -475.67188;630.92184;130.73266;,
 474.18643;695.81022;130.73266;,
 474.18643;695.81022;-116.20662;,
 -475.67188;630.92184;-116.20662;,
 -477.38546;500.01314;-94.26550;,
 425.95655;569.81871;-94.26550;,
 425.95655;569.81871;79.95587;,
 -477.38546;500.01314;79.95587;,
 -392.31473;507.91627;-81.24490;,
 -284.91726;516.86656;-81.24490;,
 -299.39644;398.26878;-66.76565;,
 -377.83550;398.26878;-66.76565;,
 -312.03636;182.14323;-88.07325;,
 -365.19573;182.14323;-88.07325;,
 -241.40291;-3.49851;-115.09243;,
 -435.82921;-3.49851;-115.09243;,
 -284.91726;516.86656;-81.24490;,
 -284.91726;516.86656;-27.54625;,
 -299.39644;398.26878;-27.54625;,
 -299.39644;398.26878;-66.76565;,
 -284.91726;516.86656;26.15237;,
 -299.39644;398.26878;11.67316;,
 -278.08916;182.14323;-27.54625;,
 -312.03636;182.14323;-88.07325;,
 -278.08916;182.14323;32.98071;,
 -245.50962;-3.49851;-28.65154;,
 -241.40291;-3.49851;-115.09243;,
 -220.81263;-3.49851;61.10530;,
 -284.91726;516.86656;26.15237;,
 -392.31473;507.91627;26.15237;,
 -377.83550;398.26878;11.67316;,
 -299.39644;398.26878;11.67316;,
 -399.14312;182.14323;32.98071;,
 -278.08916;182.14323;32.98071;,
 -456.11539;-3.49851;59.99993;,
 -220.81263;-3.49851;61.10530;,
 -392.31473;507.91627;26.15237;,
 -392.31473;507.91627;-27.54625;,
 -377.83550;398.26878;-27.54625;,
 -377.83550;398.26878;11.67316;,
 -392.31473;507.91627;-81.24490;,
 -377.83550;398.26878;-66.76565;,
 -399.14312;182.14323;-27.54625;,
 -399.14312;182.14323;32.98071;,
 -365.19573;182.14323;-88.07325;,
 -432.02657;-3.49851;-27.54625;,
 -456.11539;-3.49851;59.99993;,
 -435.82921;-3.49851;-115.09243;,
 -392.31473;507.91627;26.15237;,
 -284.91726;516.86656;26.15237;,
 -284.91726;516.86656;-27.54625;,
 -392.31473;507.91627;-27.54625;,
 -284.91726;516.86656;-81.24490;,
 -392.31473;507.91627;-81.24490;,
 210.02537;553.51930;-79.90873;,
 314.77747;562.79557;-79.90873;,
 296.85083;442.63892;-61.98219;,
 227.95196;442.63892;-61.98219;,
 316.90940;213.14165;-48.35020;,
 207.89312;213.14165;-48.35020;,
 343.23284;-2.46116;-117.73825;,
 181.57006;-2.46116;-117.73825;,
 314.77747;562.79557;-79.90873;,
 314.77747;562.79557;-27.53264;,
 296.85083;442.63892;-27.53264;,
 296.85083;442.63892;-61.98219;,
 314.77747;562.79557;24.84344;,
 296.85083;442.63892;6.91689;,
 322.32764;213.14165;-27.53264;,
 316.90940;213.14165;-48.35020;,
 320.85164;213.14165;48.29956;,
 375.30420;-2.46116;-27.53264;,
 343.23284;-2.46116;-117.73825;,
 352.60706;-2.46116;62.67294;,
 314.77747;562.79557;24.84344;,
 210.02537;553.51930;24.84344;,
 227.95196;442.63892;6.91689;,
 296.85083;442.63892;6.91689;,
 203.95108;213.14165;48.29956;,
 320.85164;213.14165;48.29956;,
 172.19575;-2.46116;62.67294;,
 352.60706;-2.46116;62.67294;,
 210.02537;553.51930;24.84344;,
 210.02537;553.51930;-27.53264;,
 227.95196;442.63892;-27.53264;,
 227.95196;442.63892;6.91689;,
 210.02537;553.51930;-79.90873;,
 227.95196;442.63892;-61.98219;,
 202.47513;213.14165;-27.53264;,
 203.95108;213.14165;48.29956;,
 207.89312;213.14165;-48.35020;,
 149.49816;-2.46116;-27.53264;,
 172.19575;-2.46116;62.67294;,
 181.57006;-2.46116;-117.73825;,
 210.02537;553.51930;24.84344;,
 314.77747;562.79557;24.84344;,
 314.77747;562.79557;-27.53264;,
 210.02537;553.51930;-27.53264;,
 314.77747;562.79557;-79.90873;,
 210.02537;553.51930;-79.90873;;
 
 46;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;35,34,38,39;,
 4;34,37,40,38;,
 4;39,38,41,42;,
 4;38,40,43,41;,
 4;44,45,46,47;,
 4;47,46,48,49;,
 4;49,48,50,51;,
 4;52,53,54,55;,
 4;53,56,57,54;,
 4;55,54,58,59;,
 4;54,57,60,58;,
 4;59,58,61,62;,
 4;58,60,63,61;,
 4;64,65,66,67;,
 4;67,66,68,69;,
 4;70,71,72,73;,
 4;73,72,74,75;,
 4;75,74,76,77;,
 4;78,79,80,81;,
 4;79,82,83,80;,
 4;81,80,84,85;,
 4;80,83,86,84;,
 4;85,84,87,88;,
 4;84,86,89,87;,
 4;90,91,92,93;,
 4;93,92,94,95;,
 4;95,94,96,97;,
 4;98,99,100,101;,
 4;99,102,103,100;,
 4;101,100,104,105;,
 4;100,103,106,104;,
 4;105,104,107,108;,
 4;104,106,109,107;,
 4;110,111,112,113;,
 4;113,112,114,115;;
 
 MeshMaterialList {
  6;
  46;
  3,
  4,
  3,
  4,
  2,
  2,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  5,
  5,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  5,
  5;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/rubble.jpeg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/rubble.jpeg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/rubble.jpeg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/rubble.jpeg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/rubble.jpeg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  68;
  0.012405;-0.170737;-0.985239;,
  0.933912;-0.357504;-0.000000;,
  0.027038;-0.372054;0.927817;,
  -0.999914;0.013089;0.000000;,
  -0.068155;0.997675;0.000000;,
  0.077045;-0.997028;-0.000000;,
  0.005101;-0.126665;-0.991932;,
  0.002567;-0.014367;-0.999894;,
  0.000000;0.121103;-0.992640;,
  0.000000;0.144027;-0.989574;,
  0.992630;-0.121187;-0.000000;,
  0.997663;-0.023999;-0.063981;,
  0.975167;0.162817;-0.150132;,
  0.953168;0.249312;-0.171215;,
  0.999933;-0.011607;-0.000000;,
  0.985585;0.156159;-0.065089;,
  0.968408;0.213004;-0.129676;,
  0.005101;-0.126664;0.991933;,
  -0.991394;-0.130916;0.000000;,
  0.002567;-0.014367;0.999894;,
  -0.997530;-0.028932;-0.064013;,
  -0.001162;0.122197;0.992505;,
  -0.975021;0.163225;-0.150635;,
  -0.002323;0.146208;0.989251;,
  -0.952782;0.250108;-0.172199;,
  0.992630;-0.121187;-0.000000;,
  0.991100;-0.036360;-0.128061;,
  0.957474;0.168290;-0.234355;,
  0.934806;0.284802;-0.212192;,
  -0.991393;-0.130916;0.000000;,
  -0.999864;-0.016510;0.000000;,
  -0.991393;-0.130916;0.000000;,
  -0.990899;-0.041300;-0.128117;,
  -0.985522;0.156556;-0.065088;,
  -0.957160;0.168692;-0.235347;,
  -0.968236;0.213786;-0.129672;,
  -0.934121;0.285587;-0.214146;,
  -0.083050;0.996545;0.000000;,
  -0.083050;0.996545;0.000000;,
  0.006619;-0.154546;-0.987963;,
  0.003313;-0.107044;-0.994249;,
  0.000000;0.125684;-0.992070;,
  0.000000;0.306358;-0.951916;,
  0.989053;-0.147561;-0.000000;,
  0.999318;-0.022336;-0.029420;,
  0.984727;0.159865;-0.068959;,
  0.972981;0.216772;-0.079478;,
  0.999798;-0.019495;0.004877;,
  0.985472;0.154525;0.070473;,
  0.971171;0.199252;0.130860;,
  0.006619;-0.154546;0.987963;,
  -0.987181;-0.159603;0.000000;,
  0.003356;0.011617;0.999927;,
  -0.999162;-0.028437;-0.029442;,
  0.000000;0.122179;0.992508;,
  -0.984727;0.159866;-0.068957;,
  0.000000;0.066518;0.997785;,
  -0.972981;0.216773;-0.079475;,
  0.997650;-0.025155;-0.063728;,
  0.964729;0.162094;-0.207422;,
  0.931443;0.224635;-0.286275;,
  -0.999661;-0.025586;0.004881;,
  -0.997475;-0.031258;-0.063775;,
  -0.985472;0.154526;0.070474;,
  -0.964730;0.162095;-0.207418;,
  -0.971171;0.199253;0.130862;,
  -0.931444;0.224636;-0.286272;,
  -0.088209;0.996102;0.000000;;
  46;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;25,10,11,26;,
  4;10,10,14,11;,
  4;26,11,12,27;,
  4;11,14,15,12;,
  4;27,12,13,28;,
  4;12,15,16,13;,
  4;17,17,19,19;,
  4;19,19,21,21;,
  4;21,21,23,23;,
  4;29,18,20,30;,
  4;18,31,32,20;,
  4;30,20,22,33;,
  4;20,32,34,22;,
  4;33,22,24,35;,
  4;22,34,36,24;,
  4;37,37,38,38;,
  4;38,38,38,38;,
  4;39,39,40,40;,
  4;40,40,41,41;,
  4;41,41,42,42;,
  4;43,43,44,58;,
  4;43,43,47,44;,
  4;58,44,45,59;,
  4;44,47,48,45;,
  4;59,45,46,60;,
  4;45,48,49,46;,
  4;50,50,52,52;,
  4;52,52,54,54;,
  4;54,54,56,56;,
  4;51,51,53,61;,
  4;51,51,62,53;,
  4;61,53,55,63;,
  4;53,62,64,55;,
  4;63,55,57,65;,
  4;55,64,66,57;,
  4;67,67,67,67;,
  4;67,67,67,67;;
 }
 MeshTextureCoords {
  116;
  -16.166044;-31.149323;,
  21.671400;-30.286253;,
  19.325100;-24.515921;,
  -16.687418;-24.953135;,
  -3.365246;-25.421669;,
  5.831062;-25.421669;,
  3.893041;-20.727989;,
  -2.595166;-20.727989;,
  21.671400;-30.286253;,
  -16.166044;-31.149323;,
  -16.687418;-24.953135;,
  19.325100;-24.515921;,
  4.904764;-23.004322;,
  -4.291544;-23.004322;,
  -3.476102;-18.127459;,
  3.012106;-18.127459;,
  -22.239616;6.905399;,
  23.168604;7.038384;,
  23.168604;-2.618302;,
  -22.239616;-2.751286;,
  -22.321535;-2.161557;,
  20.862963;-2.018495;,
  20.862963;4.794520;,
  -22.321535;4.651459;,
  -20.644083;-20.206032;,
  -14.055767;-20.615120;,
  -14.943995;-15.194399;,
  -19.755854;-15.194399;,
  -15.719393;-5.316000;,
  -18.980465;-5.316000;,
  -11.386372;3.169084;,
  -23.313488;3.169084;,
  -2.811107;-25.343327;,
  -0.129854;-25.343327;,
  -0.091965;-19.413439;,
  -2.050247;-19.413439;,
  2.551397;-25.343327;,
  1.866318;-19.413439;,
  -0.147722;-8.607162;,
  -3.081091;-8.607162;,
  2.874478;-8.607162;,
  -0.288165;0.674926;,
  -4.615032;0.674926;,
  4.128900;0.674926;,
  -14.055767;-20.615120;,
  -20.644083;-20.206032;,
  -19.755854;-15.194399;,
  -14.943995;-15.194399;,
  -21.062973;-5.316000;,
  -13.636896;-5.316000;,
  -24.557947;3.169084;,
  -10.123257;3.169084;,
  2.832434;-24.895813;,
  0.151183;-24.895813;,
  0.113294;-19.413439;,
  2.071577;-19.413439;,
  -2.530069;-24.895813;,
  -1.844988;-19.413439;,
  0.169052;-8.607162;,
  3.191252;-8.607162;,
  -2.941984;-8.607162;,
  0.255101;0.674926;,
  4.689446;0.674926;,
  -4.106258;0.674926;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  16.306576;-22.290398;,
  22.732613;-22.714386;,
  21.632900;-17.222414;,
  17.406286;-17.222414;,
  22.863398;-6.732837;,
  16.175774;-6.732837;,
  24.478212;3.121670;,
  14.560981;3.121670;,
  -4.313669;-27.639778;,
  -1.698454;-27.639778;,
  -1.651544;-21.631945;,
  -3.371660;-21.631945;,
  0.916761;-27.639778;,
  0.068572;-21.631945;,
  -1.718211;-10.157083;,
  -2.743484;-10.157083;,
  2.072064;-10.157083;,
  -1.856840;0.623058;,
  -6.277015;0.623058;,
  2.706651;0.623058;,
  22.732613;-22.714386;,
  16.306576;-22.290398;,
  17.406286;-17.222414;,
  21.632900;-17.222414;,
  15.933949;-6.732837;,
  23.105234;-6.732837;,
  13.985912;3.121670;,
  25.053276;3.121670;,
  1.190876;-27.175964;,
  -1.424339;-27.175964;,
  -1.471249;-21.631945;,
  0.248866;-21.631945;,
  -4.039554;-27.175964;,
  -3.191366;-21.631945;,
  -1.404582;-10.157083;,
  2.377969;-10.157083;,
  -2.458211;-10.157083;,
  -1.265952;0.623058;,
  3.178751;0.623058;,
  -5.853976;0.623058;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
