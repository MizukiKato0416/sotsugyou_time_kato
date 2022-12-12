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
 44;
 0.00000;0.00000;-46.32861;,
 0.00000;30.79307;-30.88573;,
 21.83951;30.79307;-21.83951;,
 32.75928;0.00000;-17.17632;,
 30.88573;30.79307;0.00000;,
 46.32861;0.00000;0.00000;,
 21.83951;30.79307;21.83951;,
 32.75928;0.00000;44.13705;,
 -0.00000;30.79307;13.18201;,
 -0.00000;0.00000;28.62488;,
 -21.83952;30.79307;21.83951;,
 -32.75928;0.00000;44.13704;,
 -30.88573;30.79307;-0.00000;,
 -46.32861;0.00000;-0.00000;,
 -21.83952;30.79307;-21.83951;,
 -32.75928;0.00000;-17.17632;,
 0.00000;30.79307;-30.88573;,
 0.00000;0.00000;-46.32861;,
 0.00000;41.79606;-15.44287;,
 10.91976;41.79606;-10.91976;,
 15.44287;41.79606;0.00000;,
 10.91976;41.79606;10.91976;,
 -0.00000;41.79606;15.44287;,
 -10.91976;41.79606;10.91975;,
 -15.44287;41.79606;-0.00000;,
 -10.91976;41.79606;-10.91975;,
 0.00000;41.79606;-15.44287;,
 0.00000;49.21178;0.00000;,
 0.00000;49.21178;0.00000;,
 0.00000;49.21178;0.00000;,
 0.00000;49.21178;0.00000;,
 0.00000;49.21178;0.00000;,
 0.00000;49.21178;0.00000;,
 0.00000;49.21178;0.00000;,
 0.00000;49.21178;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;-46.32861;,
 32.75928;0.00000;-17.17632;,
 46.32861;0.00000;0.00000;,
 32.75928;0.00000;44.13705;,
 -0.00000;0.00000;28.62488;,
 -32.75928;0.00000;44.13704;,
 -46.32861;0.00000;-0.00000;,
 -32.75928;0.00000;-17.17632;;
 
 32;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;1,18,19,2;,
 4;2,19,20,4;,
 4;4,20,21,6;,
 4;6,21,22,8;,
 4;8,22,23,10;,
 4;10,23,24,12;,
 4;12,24,25,14;,
 4;14,25,26,16;,
 3;18,27,19;,
 3;19,28,20;,
 3;20,29,21;,
 3;21,30,22;,
 3;22,31,23;,
 3;23,32,24;,
 3;24,33,25;,
 3;25,34,26;,
 3;35,36,37;,
 3;35,37,38;,
 3;35,38,39;,
 3;35,39,40;,
 3;35,40,41;,
 3;35,41,42;,
 3;35,42,43;,
 3;35,43,36;;
 
 MeshMaterialList {
  2;
  32;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.288627;0.288627;0.288627;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  33;
  0.516363;0.277958;-0.810005;,
  0.685536;0.305079;-0.661035;,
  0.903073;0.418746;-0.095455;,
  0.838853;0.452426;0.302715;,
  -0.000000;0.467097;0.884206;,
  0.358378;0.436071;0.825474;,
  -0.903073;0.418746;-0.095455;,
  -0.685536;0.305079;-0.661035;,
  0.188675;0.680250;-0.708281;,
  0.577549;0.589604;-0.564627;,
  0.763219;0.644355;-0.048005;,
  0.719319;0.637926;0.275010;,
  -0.000000;0.318328;0.947981;,
  0.169025;0.313747;0.934341;,
  -0.763219;0.644355;-0.048005;,
  -0.577549;0.589604;-0.564627;,
  0.000000;0.861364;-0.507989;,
  0.359202;0.861364;-0.359202;,
  0.507989;0.861364;0.000000;,
  0.396774;0.872752;0.284384;,
  -0.000000;0.600366;0.799725;,
  -0.244578;0.751445;0.612791;,
  -0.507989;0.861364;-0.000000;,
  -0.359202;0.861364;-0.359202;,
  0.000000;1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.358378;0.436071;0.825474;,
  -0.169026;0.313747;0.934341;,
  -0.838853;0.452426;0.302715;,
  -0.719319;0.637926;0.275010;,
  -0.516363;0.277958;-0.810005;,
  0.030920;0.171762;0.984653;,
  -0.564204;0.791870;0.233701;;
  32;
  4;0,8,9,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;26,27,12,4;,
  4;4,12,13,5;,
  4;28,29,14,6;,
  4;6,14,15,7;,
  4;7,15,30,30;,
  4;8,16,17,9;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;27,31,20,12;,
  4;12,20,21,13;,
  4;29,32,22,14;,
  4;14,22,23,15;,
  4;15,23,16,8;,
  3;16,24,17;,
  3;17,24,18;,
  3;18,24,19;,
  3;19,24,20;,
  3;20,24,21;,
  3;21,24,22;,
  3;22,24,23;,
  3;23,24,16;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;;
 }
 MeshTextureCoords {
  44;
  0.000000;1.000000;,
  0.000000;0.666667;,
  0.125000;0.666667;,
  0.125000;1.000000;,
  0.250000;0.666667;,
  0.250000;1.000000;,
  0.375000;0.666667;,
  0.375000;1.000000;,
  0.500000;0.666667;,
  0.500000;1.000000;,
  0.625000;0.666667;,
  0.625000;1.000000;,
  0.750000;0.666667;,
  0.750000;1.000000;,
  0.875000;0.666667;,
  0.875000;1.000000;,
  1.000000;0.666667;,
  1.000000;1.000000;,
  0.000000;0.333333;,
  0.125000;0.333333;,
  0.250000;0.333333;,
  0.375000;0.333333;,
  0.500000;0.333333;,
  0.625000;0.333333;,
  0.750000;0.333333;,
  0.875000;0.333333;,
  1.000000;0.333333;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}