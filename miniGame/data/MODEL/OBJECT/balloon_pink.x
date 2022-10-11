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
 88;
 0.00000;132.90000;0.00000;,
 17.31828;128.02830;-17.31828;,
 0.00000;128.02830;-24.49174;,
 24.49174;128.02830;0.00000;,
 17.31828;128.02830;17.31828;,
 0.00000;128.02830;24.49174;,
 -17.31828;128.02830;17.31828;,
 -24.49174;128.02830;0.00000;,
 -17.31828;128.02830;-17.31828;,
 0.00000;128.02830;-24.49174;,
 17.31828;128.02830;-17.31828;,
 32.00000;114.15484;-32.00000;,
 0.00000;114.15484;-45.25484;,
 45.25484;114.15484;0.00000;,
 32.00000;114.15484;32.00000;,
 0.00000;114.15484;45.25484;,
 -32.00000;114.15484;32.00000;,
 -45.25484;114.15484;0.00000;,
 -32.00000;114.15484;-32.00000;,
 0.00000;114.15484;-45.25484;,
 0.00000;114.15484;-45.25484;,
 32.00000;114.15484;-32.00000;,
 41.81002;93.39174;-41.81002;,
 0.00000;93.39174;-59.12828;,
 59.12828;93.39174;0.00000;,
 41.81002;93.39174;-41.81002;,
 41.81002;93.39174;41.81002;,
 32.00000;114.15484;32.00000;,
 0.00000;114.15484;45.25484;,
 0.00000;93.39174;59.12828;,
 41.81002;93.39174;41.81002;,
 -32.00000;114.15484;32.00000;,
 -41.81002;93.39174;41.81000;,
 -59.12828;93.39174;0.00000;,
 -41.81002;93.39174;41.81000;,
 -41.81002;93.39174;-41.81000;,
 -32.00000;114.15484;-32.00000;,
 -41.81002;93.39174;-41.81000;,
 45.25484;68.90000;-45.25484;,
 0.00000;68.90000;-64.00000;,
 64.00000;68.90000;0.00000;,
 45.25484;68.90000;-45.25484;,
 45.25484;68.90000;45.25484;,
 0.00000;68.90000;64.00000;,
 45.25484;68.90000;45.25484;,
 -45.25484;68.90000;45.25482;,
 -64.00000;68.90000;0.00000;,
 -45.25484;68.90000;45.25482;,
 -45.25484;68.90000;-45.25482;,
 -45.25484;68.90000;-45.25482;,
 37.62902;44.40826;-37.62902;,
 0.00000;44.40826;-53.21546;,
 53.21546;44.40826;0.00000;,
 37.62902;44.40826;-37.62902;,
 37.62902;44.40826;37.62902;,
 0.00000;44.40826;53.21546;,
 37.62902;44.40826;37.62902;,
 -37.62902;44.40826;37.62900;,
 -53.21546;44.40826;0.00000;,
 -37.62902;44.40826;37.62900;,
 -37.62902;44.40826;-37.62902;,
 -37.62902;44.40826;-37.62902;,
 28.80000;23.64516;-28.80000;,
 0.00000;23.64516;-40.72936;,
 40.72936;23.64516;0.00000;,
 28.80000;23.64516;-28.80000;,
 28.80000;23.64516;28.80000;,
 0.00000;23.64516;40.72936;,
 28.80000;23.64516;28.80000;,
 -28.80000;23.64516;28.80000;,
 -40.72936;23.64516;0.00000;,
 -28.80000;23.64516;28.80000;,
 -28.80000;23.64516;-28.80000;,
 -28.80000;23.64516;-28.80000;,
 0.00000;23.64516;-40.72936;,
 15.58644;9.77172;-15.58644;,
 0.00000;9.77172;-22.04256;,
 22.04256;9.77172;0.00000;,
 15.58644;9.77172;15.58644;,
 0.00000;23.64516;40.72936;,
 0.00000;9.77172;22.04256;,
 -15.58646;9.77172;15.58644;,
 -22.04256;9.77172;0.00000;,
 -15.58646;9.77172;-15.58644;,
 0.00000;23.64516;-40.72936;,
 0.00000;9.77172;-22.04256;,
 0.00000;0.10000;0.00000;,
 0.00000;0.10000;0.00000;;
 
 64;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;9,10,11,12;,
 4;10,3,13,11;,
 4;3,4,14,13;,
 4;4,5,15,14;,
 4;5,6,16,15;,
 4;6,7,17,16;,
 4;7,8,18,17;,
 4;8,2,19,18;,
 4;20,21,22,23;,
 4;11,13,24,25;,
 4;13,14,26,24;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;16,17,33,34;,
 4;17,18,35,33;,
 4;36,20,23,37;,
 4;23,22,38,39;,
 4;25,24,40,41;,
 4;24,26,42,40;,
 4;30,29,43,44;,
 4;29,32,45,43;,
 4;34,33,46,47;,
 4;33,35,48,46;,
 4;37,23,39,49;,
 4;39,38,50,51;,
 4;41,40,52,53;,
 4;40,42,54,52;,
 4;44,43,55,56;,
 4;43,45,57,55;,
 4;47,46,58,59;,
 4;46,48,60,58;,
 4;49,39,51,61;,
 4;51,50,62,63;,
 4;53,52,64,65;,
 4;52,54,66,64;,
 4;56,55,67,68;,
 4;55,57,69,67;,
 4;59,58,70,71;,
 4;58,60,72,70;,
 4;61,51,63,73;,
 4;74,65,75,76;,
 4;65,64,77,75;,
 4;64,66,78,77;,
 4;66,79,80,78;,
 4;79,71,81,80;,
 4;71,70,82,81;,
 4;70,72,83,82;,
 4;72,84,85,83;,
 3;76,75,86;,
 3;75,77,86;,
 3;77,78,86;,
 3;78,80,87;,
 3;80,81,87;,
 3;81,82,87;,
 3;82,83,87;,
 3;83,85,87;;
 
 MeshMaterialList {
  2;
  64;
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
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.000000;0.734400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/BalloonPink1_00.png";
   }
  }
 }
 MeshNormals {
  58;
  0.000000;1.000000;0.000000;,
  0.000000;0.924735;-0.380611;,
  0.269132;0.924735;-0.269132;,
  0.380611;0.924735;0.000000;,
  0.269132;0.924735;0.269132;,
  0.000000;0.924735;0.380611;,
  -0.269132;0.924735;0.269132;,
  -0.380611;0.924735;0.000000;,
  -0.269132;0.924735;-0.269132;,
  -0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;0.498494;,
  -0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;0.000000;,
  -0.498494;0.709230;-0.498494;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;-0.110450;-0.993882;,
  0.702780;-0.110450;-0.702780;,
  0.993882;-0.110450;-0.000000;,
  0.702780;-0.110450;0.702780;,
  -0.000000;-0.110450;0.993882;,
  -0.702781;-0.110450;0.702780;,
  -0.993882;-0.110450;0.000000;,
  -0.702781;-0.110450;-0.702780;,
  -0.000000;-0.460315;-0.887756;,
  0.627738;-0.460315;-0.627738;,
  0.887756;-0.460315;-0.000000;,
  0.627738;-0.460315;0.627738;,
  -0.000000;-0.460315;0.887756;,
  -0.627738;-0.460315;0.627738;,
  -0.887756;-0.460315;0.000000;,
  -0.627738;-0.460315;-0.627738;,
  0.000000;-0.674092;-0.738647;,
  0.522302;-0.674092;-0.522302;,
  0.738647;-0.674092;-0.000000;,
  0.522302;-0.674092;0.522302;,
  -0.000000;-0.674092;0.738647;,
  -0.522302;-0.674092;0.522302;,
  -0.738647;-0.674092;0.000000;,
  -0.522302;-0.674092;-0.522302;,
  0.000000;-0.865246;-0.501348;,
  0.354506;-0.865246;-0.354506;,
  0.501348;-0.865246;-0.000000;,
  0.354506;-0.865246;0.354506;,
  0.000000;-0.865246;0.501348;,
  -0.354506;-0.865246;0.354506;,
  -0.501348;-0.865246;0.000000;,
  -0.354506;-0.865246;-0.354506;,
  0.000000;-1.000000;-0.000000;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;;
 }
 MeshTextureCoords {
  88;
  0.750000;0.000000;,
  1.141550;0.122340;,
  1.000000;0.110080;,
  0.250000;0.133080;,
  0.358450;0.122340;,
  0.500000;0.110080;,
  0.641550;0.122340;,
  0.750000;0.133080;,
  0.858450;0.122340;,
  0.000000;0.110080;,
  0.141550;0.122340;,
  0.141550;0.246710;,
  0.000000;0.228380;,
  0.250000;0.261640;,
  0.358450;0.246710;,
  0.500000;0.228380;,
  0.641550;0.246710;,
  0.750000;0.261640;,
  0.858450;0.246710;,
  1.000000;0.228380;,
  0.500000;-0.789189;,
  0.739249;-0.789189;,
  0.812594;-0.633954;,
  0.500000;-0.633954;,
  0.250000;0.384240;,
  0.141550;0.373960;,
  0.358450;0.373960;,
  0.271230;0.226640;,
  0.500000;0.226640;,
  0.500000;0.375070;,
  0.201090;0.375070;,
  0.728770;0.226640;,
  0.798910;0.375070;,
  0.750000;0.384240;,
  0.641550;0.373960;,
  0.858450;0.373960;,
  0.260751;-0.789189;,
  0.187406;-0.633954;,
  0.838349;-0.450841;,
  0.500000;-0.450841;,
  0.250000;0.502810;,
  0.141550;0.503090;,
  0.358450;0.503090;,
  0.500000;0.550170;,
  0.176460;0.550170;,
  0.823540;0.550170;,
  0.750000;0.502810;,
  0.641550;0.503090;,
  0.858450;0.503090;,
  0.161651;-0.450841;,
  0.781334;-0.267727;,
  0.500000;-0.267727;,
  0.250000;0.633040;,
  0.141550;0.644470;,
  0.358450;0.644470;,
  0.500000;0.725270;,
  0.230980;0.725270;,
  0.769020;0.725270;,
  0.750000;0.633040;,
  0.641550;0.644470;,
  0.858450;0.644470;,
  0.218666;-0.267727;,
  0.715324;-0.112492;,
  0.500000;-0.112492;,
  0.250000;0.759330;,
  0.141550;0.774180;,
  0.358450;0.774180;,
  0.500000;0.873710;,
  0.294100;0.873710;,
  0.705900;0.873710;,
  0.750000;0.759330;,
  0.641550;0.774180;,
  0.858450;0.774180;,
  0.284676;-0.112492;,
  0.000000;0.792180;,
  0.141550;0.890930;,
  0.000000;0.902070;,
  0.250000;0.881140;,
  0.358450;0.890930;,
  0.500000;0.792180;,
  0.500000;0.902070;,
  0.641550;0.890930;,
  0.750000;0.881140;,
  0.858450;0.890930;,
  1.000000;0.792180;,
  1.000000;0.902070;,
  -0.250000;1.000000;,
  0.750000;1.000000;;
 }
}
