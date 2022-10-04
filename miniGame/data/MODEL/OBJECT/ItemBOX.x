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
 178;
 -8.00000;20.75094;8.00000;,
 8.00000;20.75094;8.00000;,
 8.00000;20.75094;-8.00000;,
 -8.00000;20.75094;-8.00000;,
 -8.00000;18.75094;-10.00000;,
 8.00000;18.75094;-10.00000;,
 8.00000;2.75094;-10.00000;,
 -8.00000;2.75094;-10.00000;,
 -8.00000;0.75094;-8.00000;,
 8.00000;0.75094;-8.00000;,
 8.00000;0.75094;8.00000;,
 -8.00000;0.75094;8.00000;,
 -8.00000;2.75094;10.00000;,
 8.00000;2.75094;10.00000;,
 8.00000;18.75094;10.00000;,
 -8.00000;18.75094;10.00000;,
 10.00000;18.75094;8.00000;,
 10.00000;2.75094;8.00000;,
 10.00000;2.75094;-8.00000;,
 10.00000;18.75094;-8.00000;,
 -10.00000;2.75094;8.00000;,
 -10.00000;18.75094;8.00000;,
 -10.00000;18.75094;-8.00000;,
 -10.00000;2.75094;-8.00000;,
 8.00000;20.59870;-8.76537;,
 -8.00000;20.59870;-8.76537;,
 -8.00000;20.59870;-8.76537;,
 8.00000;20.59870;-8.76537;,
 8.00000;20.16515;-9.41421;,
 -8.00000;20.16515;-9.41421;,
 8.00000;19.51631;-9.84776;,
 -8.00000;19.51631;-9.84776;,
 -8.00000;0.90318;-8.76537;,
 8.00000;0.90318;-8.76537;,
 -8.00000;1.33672;-9.41421;,
 8.00000;1.33672;-9.41421;,
 -8.00000;1.98557;-9.84776;,
 8.00000;1.98557;-9.84776;,
 8.00000;1.33672;-9.41421;,
 -8.00000;1.33672;-9.41421;,
 -8.00000;20.59870;8.76537;,
 8.00000;20.59870;8.76537;,
 8.00000;20.75094;8.00000;,
 -8.00000;20.75094;8.00000;,
 -8.00000;20.16515;9.41421;,
 8.00000;20.16515;9.41421;,
 8.00000;20.59870;8.76537;,
 -8.00000;20.59870;8.76537;,
 -8.00000;19.51631;9.84776;,
 8.00000;19.51631;9.84776;,
 -8.00000;0.75094;8.00000;,
 8.00000;0.75094;8.00000;,
 8.00000;0.90318;8.76537;,
 -8.00000;0.90318;8.76537;,
 8.00000;1.33672;9.41421;,
 -8.00000;1.33672;9.41421;,
 8.00000;1.98557;9.84776;,
 -8.00000;1.98557;9.84776;,
 8.76537;20.59870;8.00000;,
 8.76537;20.59870;-8.00000;,
 9.41421;20.16515;8.00000;,
 9.41421;20.16515;-8.00000;,
 9.41421;20.16515;-8.00000;,
 9.41421;20.16515;8.00000;,
 9.84776;19.51631;8.00000;,
 9.84776;19.51631;-8.00000;,
 8.76537;0.90318;-8.00000;,
 8.76537;0.90318;8.00000;,
 9.41421;1.33672;-8.00000;,
 9.41421;1.33672;8.00000;,
 9.84776;1.98557;-8.00000;,
 9.84776;1.98557;8.00000;,
 9.84776;1.98557;8.00000;,
 9.84776;1.98557;-8.00000;,
 -8.76537;20.59870;-8.00000;,
 -8.76537;20.59870;8.00000;,
 -9.41421;20.16515;-8.00000;,
 -9.41421;20.16515;8.00000;,
 -9.84776;19.51631;-8.00000;,
 -9.84776;19.51631;8.00000;,
 -8.76537;0.90318;8.00000;,
 -8.76537;0.90318;-8.00000;,
 -9.41421;1.33672;8.00000;,
 -9.41421;1.33672;-8.00000;,
 -9.84776;1.98557;8.00000;,
 -9.84776;1.98557;-8.00000;,
 8.76537;18.75094;-9.84776;,
 8.76537;2.75094;-9.84776;,
 8.76537;2.75094;-9.84776;,
 8.76537;18.75094;-9.84776;,
 9.41421;18.75094;-9.41421;,
 9.41421;2.75094;-9.41421;,
 9.41421;2.75094;-9.41421;,
 9.41421;18.75094;-9.41421;,
 9.84776;18.75094;-8.76537;,
 9.84776;2.75094;-8.76537;,
 9.84776;2.75094;-8.76537;,
 9.84776;18.75094;-8.76537;,
 8.76537;2.75094;9.84776;,
 8.76537;18.75094;9.84776;,
 9.41421;2.75094;9.41421;,
 9.41421;18.75094;9.41421;,
 9.41421;18.75094;9.41421;,
 9.41421;2.75094;9.41421;,
 9.84776;2.75094;8.76537;,
 9.84776;18.75094;8.76537;,
 -8.76537;2.75094;-9.84776;,
 -8.76537;18.75094;-9.84776;,
 -9.41421;2.75094;-9.41421;,
 -9.41421;18.75094;-9.41421;,
 -9.41421;18.75094;-9.41421;,
 -9.41421;2.75094;-9.41421;,
 -9.84776;2.75094;-8.76537;,
 -9.84776;18.75094;-8.76537;,
 -8.76537;18.75094;9.84776;,
 -8.76537;2.75094;9.84776;,
 -9.41421;18.75094;9.41421;,
 -9.41421;2.75094;9.41421;,
 -9.41421;2.75094;9.41421;,
 -9.41421;18.75094;9.41421;,
 -9.84776;18.75094;8.76537;,
 -9.84776;2.75094;8.76537;,
 8.76537;20.59870;-8.00000;,
 9.41421;20.16515;-8.00000;,
 9.00000;20.16515;-9.00000;,
 9.00000;20.16515;-9.00000;,
 9.60021;19.51631;-8.92388;,
 9.60021;19.51631;-8.92388;,
 8.92388;19.51631;-9.60021;,
 9.84776;19.51631;-8.00000;,
 -9.00000;20.16515;-9.00000;,
 -9.00000;20.16515;-9.00000;,
 -9.60021;19.51631;-8.92388;,
 -8.92388;19.51631;-9.60021;,
 -8.92388;19.51631;-9.60021;,
 9.00000;1.33672;-9.00000;,
 9.60021;1.98557;-8.92388;,
 9.84776;1.98557;-8.00000;,
 9.41421;1.33672;-8.00000;,
 9.00000;1.33672;-9.00000;,
 8.92388;1.98557;-9.60021;,
 8.00000;20.59870;8.76537;,
 9.00000;20.16515;9.00000;,
 8.76537;20.59870;8.00000;,
 9.00000;20.16515;9.00000;,
 8.00000;20.16515;9.41421;,
 9.60021;19.51631;8.92388;,
 8.92388;19.51631;9.60021;,
 9.60021;19.51631;8.92388;,
 9.00000;20.16515;9.00000;,
 -9.00000;1.33672;-9.00000;,
 -9.60021;1.98557;-8.92388;,
 -8.92388;1.98557;-9.60021;,
 -8.92388;1.98557;-9.60021;,
 -9.00000;1.33672;-9.00000;,
 8.00000;0.90318;8.76537;,
 9.00000;1.33672;9.00000;,
 8.00000;1.33672;9.41421;,
 9.41421;1.33672;8.00000;,
 9.60021;1.98557;8.92388;,
 9.00000;1.33672;9.00000;,
 9.00000;1.33672;9.00000;,
 9.60021;1.98557;8.92388;,
 8.92388;1.98557;9.60021;,
 -8.00000;20.59870;8.76537;,
 -9.00000;20.16515;9.00000;,
 -8.00000;20.16515;9.41421;,
 -9.60021;19.51631;8.92388;,
 -8.92388;19.51631;9.60021;,
 -8.92388;19.51631;9.60021;,
 -9.00000;20.16515;9.00000;,
 -8.00000;0.90318;8.76537;,
 -9.00000;1.33672;9.00000;,
 -8.00000;1.33672;9.41421;,
 -9.60021;1.98557;8.92388;,
 -8.92388;1.98557;9.60021;,
 -9.60021;1.98557;8.92388;,
 -9.00000;1.33672;9.00000;;
 
 182;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;3,2,24,25;,
 4;26,27,28,29;,
 4;29,28,30,31;,
 4;31,30,5,4;,
 4;32,33,9,8;,
 4;34,35,33,32;,
 4;36,37,38,39;,
 4;7,6,37,36;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,45,44;,
 4;15,14,49,48;,
 4;50,51,52,53;,
 4;53,52,54,55;,
 4;55,54,56,57;,
 4;57,56,13,12;,
 4;2,1,58,59;,
 4;59,58,60,61;,
 4;62,63,64,65;,
 4;65,64,16,19;,
 4;10,9,66,67;,
 4;67,66,68,69;,
 4;69,68,70,71;,
 4;72,73,18,17;,
 4;0,3,74,75;,
 4;75,74,76,77;,
 4;77,76,78,79;,
 4;79,78,22,21;,
 4;8,11,80,81;,
 4;81,80,82,83;,
 4;83,82,84,85;,
 4;85,84,20,23;,
 4;6,5,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,19,18;,
 4;14,13,98,99;,
 4;99,98,100,101;,
 4;102,103,104,105;,
 4;105,104,17,16;,
 4;4,7,106,107;,
 4;107,106,108,109;,
 4;110,111,112,113;,
 4;113,112,23,22;,
 4;12,15,114,115;,
 4;115,114,116,117;,
 4;118,119,120,121;,
 4;121,120,21,20;,
 3;2,59,24;,
 3;122,123,124;,
 3;125,24,59;,
 3;27,124,28;,
 3;62,65,126;,
 3;127,124,123;,
 3;124,127,128;,
 3;128,28,124;,
 3;28,128,30;,
 3;65,19,97;,
 3;94,127,129;,
 3;127,94,93;,
 3;93,128,127;,
 3;128,93,86;,
 3;86,30,128;,
 3;30,86,5;,
 3;25,74,3;,
 3;130,76,74;,
 3;74,25,130;,
 3;29,131,26;,
 3;132,78,76;,
 3;76,130,132;,
 3;133,132,130;,
 3;131,29,134;,
 3;31,134,29;,
 3;113,22,78;,
 3;78,132,113;,
 3;110,113,132;,
 3;132,133,110;,
 3;107,109,134;,
 3;134,31,107;,
 3;4,107,31;,
 3;33,66,9;,
 3;135,68,66;,
 3;66,33,135;,
 3;35,135,33;,
 3;136,137,138;,
 3;138,139,136;,
 3;140,136,139;,
 3;139,38,140;,
 3;37,140,38;,
 3;96,18,73;,
 3;137,136,95;,
 3;92,95,136;,
 3;136,140,92;,
 3;87,92,140;,
 3;140,37,87;,
 3;6,87,37;,
 3;141,58,1;,
 3;142,63,143;,
 3;58,141,144;,
 3;145,144,141;,
 3;146,64,63;,
 3;63,142,146;,
 3;147,148,149;,
 3;149,45,147;,
 3;49,147,45;,
 3;105,16,64;,
 3;64,146,105;,
 3;102,105,146;,
 3;148,147,101;,
 3;99,101,147;,
 3;147,49,99;,
 3;14,99,49;,
 3;8,81,32;,
 3;81,83,150;,
 3;150,32,81;,
 3;32,150,34;,
 3;83,85,151;,
 3;151,150,83;,
 3;150,151,152;,
 3;153,39,154;,
 3;39,153,36;,
 3;85,23,112;,
 3;112,151,85;,
 3;151,112,111;,
 3;111,152,151;,
 3;153,108,106;,
 3;106,36,153;,
 3;36,106,7;,
 3;10,67,155;,
 3;67,69,156;,
 3;156,155,67;,
 3;155,156,157;,
 3;158,72,159;,
 3;159,160,158;,
 3;161,162,163;,
 3;163,54,161;,
 3;54,163,56;,
 3;72,17,104;,
 3;104,159,72;,
 3;159,104,103;,
 3;100,163,162;,
 3;163,100,98;,
 3;98,56,163;,
 3;56,98,13;,
 3;0,75,164;,
 3;75,77,165;,
 3;165,164,75;,
 3;164,165,166;,
 3;77,79,167;,
 3;167,165,77;,
 3;165,167,168;,
 3;169,44,170;,
 3;44,169,48;,
 3;79,21,120;,
 3;120,167,79;,
 3;167,120,119;,
 3;119,168,167;,
 3;169,116,114;,
 3;114,48,169;,
 3;48,114,15;,
 3;171,80,11;,
 3;172,82,80;,
 3;80,171,172;,
 3;173,172,171;,
 3;174,84,82;,
 3;82,172,174;,
 3;175,176,177;,
 3;177,55,175;,
 3;57,175,55;,
 3;121,20,84;,
 3;84,174,121;,
 3;118,121,174;,
 3;176,175,117;,
 3;115,117,175;,
 3;175,57,115;,
 3;12,115,57;;
 
 MeshMaterialList {
  4;
  182;
  0,
  1,
  0,
  3,
  2,
  0,
  0,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  2,
  2,
  0,
  0,
  0,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  2,
  1,
  2,
  3,
  3,
  2,
  2,
  1,
  1,
  0,
  0,
  3,
  3,
  0,
  0,
  0,
  1,
  0,
  1,
  2,
  1,
  1,
  1,
  1,
  2,
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
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  2,
  0,
  0,
  2,
  2,
  3,
  3,
  3,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  0,
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
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  2,
  2,
  3,
  3,
  3,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  0,
  0,
  0,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/PLAYER/ItemBOX";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/PLAYER/ItemBOX";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/PLAYER/ItemBOX";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/PLAYER/ItemBOX";
   }
  }
 }
 MeshNormals {
  120;
  -0.097566;0.990435;0.097566;,
  0.097566;0.990435;0.097566;,
  -0.097566;0.990435;-0.097566;,
  0.097566;0.990435;-0.097566;,
  -0.097566;0.097566;-0.990435;,
  0.097566;0.097566;-0.990435;,
  -0.097566;-0.097566;-0.990435;,
  0.097566;-0.097566;-0.990435;,
  -0.097566;-0.990435;-0.097566;,
  0.097566;-0.990435;-0.097566;,
  -0.097566;-0.990435;0.097566;,
  0.097566;-0.990435;0.097566;,
  -0.097566;-0.097566;0.990435;,
  0.097566;-0.097566;0.990435;,
  -0.097566;0.097566;0.990435;,
  0.097566;0.097566;0.990435;,
  0.990435;0.097566;0.097566;,
  0.990435;-0.097566;0.097566;,
  0.990435;0.097566;-0.097566;,
  0.990435;-0.097566;-0.097566;,
  -0.990435;-0.097566;0.097566;,
  -0.990435;0.097566;0.097566;,
  -0.990435;-0.097566;-0.097566;,
  -0.990435;0.097566;-0.097566;,
  -0.149549;0.917628;-0.368230;,
  0.149549;0.917628;-0.368230;,
  -0.151335;0.689779;-0.708028;,
  0.151335;0.689779;-0.708028;,
  -0.134929;0.354970;-0.925089;,
  0.134929;0.354970;-0.925089;,
  -0.149547;-0.917630;-0.368225;,
  0.149547;-0.917630;-0.368225;,
  -0.151335;-0.689779;-0.708028;,
  0.151335;-0.689779;-0.708028;,
  -0.134929;-0.354967;-0.925091;,
  0.134929;-0.354967;-0.925091;,
  -0.149549;0.917628;0.368230;,
  0.149549;0.917628;0.368230;,
  -0.151335;0.689779;0.708028;,
  0.151335;0.689779;0.708028;,
  -0.134929;0.354970;0.925089;,
  0.134929;0.354970;0.925089;,
  -0.149547;-0.917630;0.368225;,
  0.149547;-0.917630;0.368225;,
  -0.151335;-0.689779;0.708028;,
  0.151335;-0.689779;0.708028;,
  -0.134929;-0.354967;0.925091;,
  0.134929;-0.354967;0.925091;,
  0.368230;0.917628;0.149549;,
  0.368230;0.917628;-0.149549;,
  0.708028;0.689779;0.151335;,
  0.708028;0.689779;-0.151335;,
  0.925089;0.354970;0.134929;,
  0.925089;0.354970;-0.134929;,
  0.368225;-0.917630;0.149547;,
  0.368225;-0.917630;-0.149547;,
  0.708028;-0.689779;0.151335;,
  0.708028;-0.689779;-0.151335;,
  0.925091;-0.354967;0.134929;,
  0.925091;-0.354967;-0.134929;,
  -0.368230;0.917628;0.149549;,
  -0.368230;0.917628;-0.149549;,
  -0.708028;0.689779;0.151335;,
  -0.708028;0.689779;-0.151335;,
  -0.925089;0.354970;0.134929;,
  -0.925089;0.354970;-0.134929;,
  -0.368225;-0.917630;0.149547;,
  -0.368225;-0.917630;-0.149547;,
  -0.708028;-0.689779;0.151335;,
  -0.708028;-0.689779;-0.151335;,
  -0.925091;-0.354967;0.134929;,
  -0.925091;-0.354967;-0.134929;,
  0.356112;-0.121466;-0.926515;,
  0.356112;0.121466;-0.926515;,
  0.702218;-0.117385;-0.702218;,
  0.702218;0.117385;-0.702218;,
  0.926515;-0.121466;-0.356112;,
  0.926515;0.121466;-0.356112;,
  0.356112;-0.121466;0.926515;,
  0.356112;0.121466;0.926515;,
  0.702218;-0.117385;0.702218;,
  0.702218;0.117385;0.702218;,
  0.926515;-0.121466;0.356112;,
  0.926515;0.121466;0.356112;,
  -0.356112;-0.121466;-0.926515;,
  -0.356112;0.121466;-0.926515;,
  -0.702218;-0.117385;-0.702218;,
  -0.702218;0.117385;-0.702218;,
  -0.926515;-0.121466;-0.356112;,
  -0.926515;0.121466;-0.356112;,
  -0.356112;-0.121466;0.926515;,
  -0.356112;0.121466;0.926515;,
  -0.702218;-0.117385;0.702218;,
  -0.702218;0.117385;0.702218;,
  -0.926515;-0.121466;0.356112;,
  -0.926515;0.121466;0.356112;,
  0.472232;0.744308;-0.472232;,
  0.794180;0.405800;-0.452332;,
  0.452332;0.405800;-0.794180;,
  -0.472232;0.744308;-0.472232;,
  -0.794180;0.405800;-0.452332;,
  -0.452332;0.405800;-0.794180;,
  0.472231;-0.744309;-0.472231;,
  0.794181;-0.405797;-0.452333;,
  0.452333;-0.405797;-0.794181;,
  0.472232;0.744308;0.472232;,
  0.794180;0.405800;0.452332;,
  0.452332;0.405800;0.794180;,
  -0.472231;-0.744309;-0.472231;,
  -0.794181;-0.405797;-0.452333;,
  -0.452333;-0.405797;-0.794181;,
  0.472231;-0.744309;0.472231;,
  0.794181;-0.405797;0.452333;,
  0.452333;-0.405797;0.794181;,
  -0.472232;0.744308;0.472232;,
  -0.794180;0.405800;0.452332;,
  -0.452332;0.405800;0.794180;,
  -0.472231;-0.744309;0.472231;,
  -0.794181;-0.405797;0.452333;,
  -0.452333;-0.405797;0.794181;;
  182;
  4;0,1,3,2;,
  4;4,5,7,6;,
  4;8,9,11,10;,
  4;12,13,15,14;,
  4;16,17,19,18;,
  4;20,21,23,22;,
  4;2,3,25,24;,
  4;24,25,27,26;,
  4;26,27,29,28;,
  4;28,29,5,4;,
  4;30,31,9,8;,
  4;32,33,31,30;,
  4;34,35,33,32;,
  4;6,7,35,34;,
  4;36,37,1,0;,
  4;38,39,37,36;,
  4;40,41,39,38;,
  4;14,15,41,40;,
  4;10,11,43,42;,
  4;42,43,45,44;,
  4;44,45,47,46;,
  4;46,47,13,12;,
  4;3,1,48,49;,
  4;49,48,50,51;,
  4;51,50,52,53;,
  4;53,52,16,18;,
  4;11,9,55,54;,
  4;54,55,57,56;,
  4;56,57,59,58;,
  4;58,59,19,17;,
  4;0,2,61,60;,
  4;60,61,63,62;,
  4;62,63,65,64;,
  4;64,65,23,21;,
  4;8,10,66,67;,
  4;67,66,68,69;,
  4;69,68,70,71;,
  4;71,70,20,22;,
  4;7,5,73,72;,
  4;72,73,75,74;,
  4;74,75,77,76;,
  4;76,77,18,19;,
  4;15,13,78,79;,
  4;79,78,80,81;,
  4;81,80,82,83;,
  4;83,82,17,16;,
  4;4,6,84,85;,
  4;85,84,86,87;,
  4;87,86,88,89;,
  4;89,88,22,23;,
  4;12,14,91,90;,
  4;90,91,93,92;,
  4;92,93,95,94;,
  4;94,95,21,20;,
  3;3,49,25;,
  3;49,51,96;,
  3;96,25,49;,
  3;25,96,27;,
  3;51,53,97;,
  3;97,96,51;,
  3;96,97,98;,
  3;98,27,96;,
  3;27,98,29;,
  3;53,18,77;,
  3;77,97,53;,
  3;97,77,75;,
  3;75,98,97;,
  3;98,75,73;,
  3;73,29,98;,
  3;29,73,5;,
  3;24,61,2;,
  3;99,63,61;,
  3;61,24,99;,
  3;26,99,24;,
  3;100,65,63;,
  3;63,99,100;,
  3;101,100,99;,
  3;99,26,101;,
  3;28,101,26;,
  3;89,23,65;,
  3;65,100,89;,
  3;87,89,100;,
  3;100,101,87;,
  3;85,87,101;,
  3;101,28,85;,
  3;4,85,28;,
  3;31,55,9;,
  3;102,57,55;,
  3;55,31,102;,
  3;33,102,31;,
  3;103,59,57;,
  3;57,102,103;,
  3;104,103,102;,
  3;102,33,104;,
  3;35,104,33;,
  3;76,19,59;,
  3;59,103,76;,
  3;74,76,103;,
  3;103,104,74;,
  3;72,74,104;,
  3;104,35,72;,
  3;7,72,35;,
  3;37,48,1;,
  3;105,50,48;,
  3;48,37,105;,
  3;39,105,37;,
  3;106,52,50;,
  3;50,105,106;,
  3;107,106,105;,
  3;105,39,107;,
  3;41,107,39;,
  3;83,16,52;,
  3;52,106,83;,
  3;81,83,106;,
  3;106,107,81;,
  3;79,81,107;,
  3;107,41,79;,
  3;15,79,41;,
  3;8,67,30;,
  3;67,69,108;,
  3;108,30,67;,
  3;30,108,32;,
  3;69,71,109;,
  3;109,108,69;,
  3;108,109,110;,
  3;110,32,108;,
  3;32,110,34;,
  3;71,22,88;,
  3;88,109,71;,
  3;109,88,86;,
  3;86,110,109;,
  3;110,86,84;,
  3;84,34,110;,
  3;34,84,6;,
  3;11,54,43;,
  3;54,56,111;,
  3;111,43,54;,
  3;43,111,45;,
  3;56,58,112;,
  3;112,111,56;,
  3;111,112,113;,
  3;113,45,111;,
  3;45,113,47;,
  3;58,17,82;,
  3;82,112,58;,
  3;112,82,80;,
  3;80,113,112;,
  3;113,80,78;,
  3;78,47,113;,
  3;47,78,13;,
  3;0,60,36;,
  3;60,62,114;,
  3;114,36,60;,
  3;36,114,38;,
  3;62,64,115;,
  3;115,114,62;,
  3;114,115,116;,
  3;116,38,114;,
  3;38,116,40;,
  3;64,21,95;,
  3;95,115,64;,
  3;115,95,93;,
  3;93,116,115;,
  3;116,93,91;,
  3;91,40,116;,
  3;40,91,14;,
  3;42,66,10;,
  3;117,68,66;,
  3;66,42,117;,
  3;44,117,42;,
  3;118,70,68;,
  3;68,117,118;,
  3;119,118,117;,
  3;117,44,119;,
  3;46,119,44;,
  3;94,20,70;,
  3;70,118,94;,
  3;92,94,118;,
  3;118,119,92;,
  3;90,92,119;,
  3;119,46,90;,
  3;12,90,46;;
 }
 MeshTextureCoords {
  178;
  0.245932;0.108174;,
  0.245932;0.108174;,
  0.754068;0.108174;,
  0.754068;0.108174;,
  0.236906;0.191442;,
  0.763094;0.191442;,
  0.763094;0.830614;,
  0.236906;0.830614;,
  0.754068;0.915153;,
  0.754068;0.915153;,
  0.245932;0.915153;,
  0.245932;0.915153;,
  0.762338;0.817816;,
  0.251682;0.817816;,
  0.251682;0.184989;,
  0.762338;0.184989;,
  0.779501;0.182466;,
  0.779501;0.815292;,
  0.218600;0.815292;,
  0.218600;0.182466;,
  0.245932;0.834455;,
  0.245932;0.188872;,
  0.754068;0.188872;,
  0.754068;0.834455;,
  0.778375;0.114317;,
  0.778375;0.114317;,
  0.236906;0.117628;,
  0.763094;0.117628;,
  0.763094;0.134947;,
  0.236906;0.134947;,
  0.763094;0.160867;,
  0.236906;0.160867;,
  0.778375;0.909010;,
  0.778375;0.909010;,
  0.798981;0.891517;,
  0.798981;0.891517;,
  0.236906;0.861189;,
  0.763094;0.861189;,
  0.763094;0.887109;,
  0.236906;0.887109;,
  0.236906;0.117628;,
  0.763094;0.117628;,
  0.763094;0.111546;,
  0.236906;0.111546;,
  0.762502;0.129055;,
  0.251845;0.129055;,
  0.252025;0.111907;,
  0.762682;0.111907;,
  0.762381;0.154718;,
  0.251724;0.154718;,
  0.762895;0.896919;,
  0.252239;0.896919;,
  0.252025;0.890898;,
  0.762682;0.890898;,
  0.251845;0.873750;,
  0.762502;0.873750;,
  0.251724;0.848087;,
  0.762381;0.848087;,
  0.245932;0.114317;,
  0.754068;0.114317;,
  0.245932;0.131810;,
  0.754068;0.131810;,
  0.217703;0.126532;,
  0.778604;0.126532;,
  0.779268;0.152194;,
  0.218367;0.152194;,
  0.754068;0.909010;,
  0.245932;0.909010;,
  0.754068;0.891517;,
  0.245932;0.891517;,
  0.754068;0.865337;,
  0.245932;0.865337;,
  0.779268;0.845564;,
  0.218367;0.845564;,
  0.754068;0.114317;,
  0.245932;0.114317;,
  0.754068;0.131810;,
  0.245932;0.131810;,
  0.754068;0.157990;,
  0.245932;0.157990;,
  0.245932;0.909010;,
  0.754068;0.909010;,
  0.245932;0.891517;,
  0.754068;0.891517;,
  0.245932;0.865337;,
  0.754068;0.865337;,
  0.788264;0.191442;,
  0.788264;0.830614;,
  0.151935;0.815292;,
  0.151935;0.182466;,
  0.168126;0.182466;,
  0.168126;0.815292;,
  0.809603;0.830614;,
  0.809603;0.191442;,
  0.823861;0.191442;,
  0.823861;0.830614;,
  0.191536;0.815292;,
  0.191536;0.182466;,
  0.227296;0.817816;,
  0.227296;0.184989;,
  0.206709;0.817816;,
  0.206709;0.184989;,
  0.828181;0.182466;,
  0.828181;0.815292;,
  0.806099;0.815292;,
  0.806099;0.182466;,
  0.211736;0.830614;,
  0.211736;0.191442;,
  0.190397;0.830614;,
  0.190397;0.191442;,
  0.798981;0.188872;,
  0.798981;0.834455;,
  0.778375;0.834455;,
  0.778375;0.188872;,
  0.786808;0.184989;,
  0.786808;0.817816;,
  0.807638;0.184989;,
  0.807638;0.817816;,
  0.201019;0.834455;,
  0.201019;0.188872;,
  0.221625;0.188872;,
  0.221625;0.834455;,
  0.788264;0.117628;,
  0.809603;0.134947;,
  0.795981;0.134947;,
  0.785827;0.131810;,
  0.185600;0.152194;,
  0.815719;0.160867;,
  0.793477;0.160867;,
  0.823861;0.160867;,
  0.785827;0.131810;,
  0.204019;0.134947;,
  0.783409;0.157990;,
  0.804889;0.157990;,
  0.206523;0.160867;,
  0.785827;0.891517;,
  0.815719;0.861189;,
  0.823861;0.861189;,
  0.809603;0.887109;,
  0.795981;0.887109;,
  0.793477;0.861189;,
  0.221625;0.114317;,
  0.813026;0.126532;,
  0.777611;0.109384;,
  0.214173;0.131810;,
  0.201019;0.131810;,
  0.811276;0.152194;,
  0.222306;0.154718;,
  0.200909;0.154718;,
  0.220044;0.129055;,
  0.785827;0.891517;,
  0.783409;0.865337;,
  0.804889;0.865337;,
  0.206523;0.861189;,
  0.204019;0.887109;,
  0.221625;0.909010;,
  0.214173;0.891517;,
  0.201019;0.891517;,
  0.778604;0.871227;,
  0.811276;0.845564;,
  0.813026;0.871227;,
  0.220044;0.873750;,
  0.200909;0.848087;,
  0.222306;0.848087;,
  0.221625;0.114317;,
  0.214173;0.131810;,
  0.201019;0.131810;,
  0.216591;0.157990;,
  0.195111;0.157990;,
  0.791936;0.154718;,
  0.794533;0.129055;,
  0.221625;0.909010;,
  0.214173;0.891517;,
  0.201019;0.891517;,
  0.216591;0.865337;,
  0.791936;0.848087;,
  0.813710;0.848087;,
  0.794533;0.873750;;
 }
}
