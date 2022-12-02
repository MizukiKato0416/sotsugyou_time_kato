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
 68;
 0.00000;78.92708;-31.39910;,
 22.20252;78.92708;-22.20257;,
 41.02497;61.14093;-41.02501;,
 0.00000;61.14093;-58.01810;,
 31.39912;78.92708;-0.00002;,
 58.01807;61.14093;-0.00002;,
 22.20252;78.92708;22.20254;,
 41.02497;61.14093;41.02497;,
 0.00000;78.92708;31.39908;,
 0.00000;61.14093;58.01801;,
 -22.20252;78.92708;22.20254;,
 -41.02497;61.14093;41.02497;,
 -31.39912;78.92708;-0.00002;,
 -58.01807;61.14093;-0.00002;,
 -22.20252;78.92708;-22.20257;,
 -41.02497;61.14093;-41.02501;,
 0.00000;78.92708;-31.39910;,
 0.00000;61.14093;-58.01810;,
 53.60164;34.52206;-53.60169;,
 0.00000;34.52206;-75.80432;,
 75.80424;34.52206;-0.00002;,
 53.60164;34.52206;53.60165;,
 0.00000;34.52206;75.80421;,
 -53.60175;34.52206;53.60165;,
 -75.80424;34.52206;-0.00002;,
 -53.60175;34.52206;-53.60169;,
 0.00000;34.52206;-75.80432;,
 58.01807;3.12287;-58.01810;,
 0.00000;3.12287;-82.04995;,
 82.04993;3.12287;-0.00002;,
 58.01807;3.12287;58.01801;,
 0.00000;3.12287;82.04995;,
 -58.01807;3.12287;58.01801;,
 -82.04993;3.12287;-0.00002;,
 -58.01807;3.12287;-58.01810;,
 0.00000;3.12287;-82.04995;,
 53.60164;-28.27629;-53.60169;,
 0.00000;-28.27629;-75.80432;,
 75.80424;-28.27629;-0.00002;,
 53.60164;-28.27629;53.60165;,
 0.00000;-28.27629;75.80421;,
 -53.60175;-28.27629;53.60165;,
 -75.80424;-28.27629;-0.00002;,
 -53.60175;-28.27629;-53.60169;,
 0.00000;-28.27629;-75.80432;,
 41.02497;-54.89530;-41.02501;,
 0.00000;-54.89530;-58.01810;,
 58.01807;-54.89530;-0.00002;,
 41.02497;-54.89530;41.02497;,
 0.00000;-54.89530;58.01801;,
 -41.02497;-54.89530;41.02497;,
 -58.01807;-54.89530;-0.00002;,
 -41.02497;-54.89530;-41.02501;,
 0.00000;-54.89530;-58.01810;,
 22.20252;-72.68142;-22.20257;,
 0.00000;-72.68142;-31.39910;,
 31.39912;-72.68142;-0.00002;,
 22.20252;-72.68142;22.20254;,
 0.00000;-72.68142;31.39908;,
 -22.20252;-72.68142;22.20254;,
 -31.39912;-72.68142;-0.00002;,
 -22.20252;-72.68142;-22.20257;,
 0.00000;-72.68142;-31.39910;,
 0.00000;-78.92708;-0.00002;,
 0.00000;-78.92708;-0.00002;,
 22.20252;78.92708;22.20254;,
 -22.20252;78.92708;-22.20257;,
 -31.39912;78.92708;-0.00002;;
 
 59;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;46,45,54,55;,
 4;45,47,56,54;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 3;55,54,63;,
 3;54,56,63;,
 3;56,57,63;,
 3;57,58,63;,
 3;58,59,63;,
 3;59,60,63;,
 3;60,61,63;,
 3;61,62,64;,
 4;12,10,8,65;,
 4;6,4,1,0;,
 4;0,66,67,6;;
 
 MeshMaterialList {
  1;
  59;
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
  0;;
  Material {
   0.000000;0.709020;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.327922;0.370000;;
   TextureFilename {
    data/TEXTURE/MESH/face03.png";
   }
  }
 }
 MeshNormals {
  57;
  0.000000;0.958069;-0.286537;,
  0.270034;0.924209;-0.270035;,
  0.381887;0.924209;0.000000;,
  0.161339;0.973622;0.161340;,
  0.000000;0.924209;0.381887;,
  -0.270035;0.924209;0.270035;,
  -0.286537;0.958069;0.000000;,
  -0.270034;0.924209;-0.270035;,
  0.000000;0.709231;-0.704976;,
  0.498493;0.709231;-0.498493;,
  0.704976;0.709231;0.000000;,
  0.498493;0.709231;0.498494;,
  0.000000;0.709231;0.704976;,
  -0.498493;0.709231;0.498493;,
  -0.704976;0.709231;0.000000;,
  -0.498493;0.709231;-0.498493;,
  0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  0.000000;-0.000000;-1.000000;,
  0.707107;-0.000000;-0.707107;,
  1.000000;-0.000000;0.000000;,
  0.707107;-0.000000;0.707107;,
  0.000000;-0.000000;1.000000;,
  -0.707107;-0.000000;0.707107;,
  -1.000000;-0.000000;0.000000;,
  -0.707107;-0.000000;-0.707107;,
  0.000000;-0.384550;-0.923104;,
  0.652733;-0.384550;-0.652733;,
  0.923104;-0.384550;0.000000;,
  0.652733;-0.384550;0.652733;,
  0.000000;-0.384550;0.923104;,
  -0.652733;-0.384550;0.652733;,
  -0.923104;-0.384550;0.000000;,
  -0.652733;-0.384550;-0.652733;,
  0.000000;-0.709231;-0.704976;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;0.000000;,
  0.498494;-0.709230;0.498494;,
  0.000000;-0.709230;0.704977;,
  -0.498493;-0.709231;0.498494;,
  -0.704976;-0.709231;0.000000;,
  -0.498494;-0.709231;-0.498494;,
  0.000000;-0.924736;-0.380609;,
  0.269131;-0.924736;-0.269132;,
  0.380609;-0.924736;0.000000;,
  0.269131;-0.924736;0.269132;,
  0.000000;-0.924736;0.380610;,
  -0.269131;-0.924736;0.269132;,
  -0.380609;-0.924736;0.000000;,
  -0.269131;-0.924736;-0.269131;,
  -0.000000;-1.000000;-0.000000;;
  59;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,40,48,55;,
  3;48,49,56;,
  3;49,50,56;,
  3;50,51,56;,
  3;51,52,56;,
  3;52,53,56;,
  3;53,54,56;,
  3;54,55,56;,
  3;55,48,56;,
  4;6,5,4,3;,
  4;3,2,1,0;,
  4;0,7,6,3;;
 }
 MeshTextureCoords {
  68;
  0.044677;0.287915;,
  0.109434;0.264859;,
  0.135829;0.381903;,
  0.047940;0.407454;,
  0.173890;0.206541;,
  0.230406;0.322887;,
  0.240721;0.112012;,
  0.353188;0.236020;,
  0.705292;0.013096;,
  0.555655;0.184551;,
  0.847400;0.133852;,
  0.746621;0.259937;,
  0.914173;0.225078;,
  0.864722;0.348858;,
  0.979508;0.275609;,
  0.959548;0.397804;,
  1.044677;0.287915;,
  1.047940;0.407454;,
  0.150147;0.491800;,
  0.050554;0.515718;,
  0.255914;0.444691;,
  0.383601;0.386884;,
  0.549114;0.362785;,
  0.713260;0.412519;,
  0.841473;0.475422;,
  0.949676;0.511219;,
  1.050554;0.515718;,
  0.160147;0.595451;,
  0.053316;0.616930;,
  0.270726;0.561041;,
  0.396536;0.528703;,
  0.545281;0.523884;,
  0.696279;0.556309;,
  0.827534;0.595271;,
  0.943919;0.617542;,
  1.053316;0.616930;,
  0.168728;0.694949;,
  0.056960;0.714051;,
  0.281063;0.671215;,
  0.403263;0.656627;,
  0.541273;0.662848;,
  0.684310;0.685314;,
  0.817532;0.707906;,
  0.940606;0.719166;,
  1.056960;0.714051;,
  0.178090;0.792203;,
  0.063210;0.809219;,
  0.289488;0.776648;,
  0.406267;0.772784;,
  0.535100;0.783987;,
  0.672567;0.801598;,
  0.809039;0.814934;,
  0.939975;0.818173;,
  1.063210;0.809219;,
  0.193830;0.888720;,
  0.080290;0.903828;,
  0.298021;0.879079;,
  0.403563;0.880442;,
  0.519488;0.892595;,
  0.651620;0.908387;,
  0.798987;0.918242;,
  0.947937;0.916188;,
  1.080290;0.903828;,
  0.326469;0.979979;,
  1.326469;0.979979;,
  1.240721;0.112012;,
  -0.020492;0.275609;,
  -0.085827;0.225078;;
 }
}
