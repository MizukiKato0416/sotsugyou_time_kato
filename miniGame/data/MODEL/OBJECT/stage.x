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
 102;
 -830.79640;145.42217;-812.82574;,
 -830.79640;145.42217;814.57379;,
 -830.79640;-233.22452;814.57379;,
 -830.79640;-233.22452;-812.82574;,
 -1416.58733;470.91060;1402.62961;,
 -1416.58733;-217.15474;1402.62961;,
 -1416.58733;-217.15474;-1400.19885;,
 -1416.58733;470.91060;-1400.19885;,
 -1416.58733;470.91060;1402.62961;,
 -830.79640;145.42217;814.57379;,
 -830.79640;145.42217;-812.82574;,
 -1416.58733;470.91060;-1400.19885;,
 830.79640;147.64517;-812.82574;,
 830.79640;-233.22452;-812.82574;,
 830.79640;-233.22452;814.57379;,
 830.79640;147.64517;814.57379;,
 1416.58733;470.91060;1402.62961;,
 1416.58733;470.91060;-1400.19885;,
 1416.58733;-217.15474;-1400.19885;,
 1416.58733;-217.15474;1402.62961;,
 1416.58733;470.91060;1402.62961;,
 1416.58733;470.91060;-1400.19885;,
 830.79640;147.64517;-812.82574;,
 830.79640;147.64517;814.57379;,
 -830.09669;147.07610;-809.25162;,
 -830.09669;-231.57063;-809.25162;,
 830.09669;-231.57063;-809.25162;,
 830.09669;147.07610;-809.25162;,
 1415.46360;474.38336;-1402.94289;,
 1415.46360;-213.68167;-1402.94289;,
 -1415.46360;-213.68167;-1402.94289;,
 -1415.46360;474.38336;-1402.94289;,
 1415.46360;474.38336;-1402.94289;,
 -1415.46360;474.38336;-1402.94289;,
 -830.09669;147.07610;-809.25162;,
 830.09669;147.07610;-809.25162;,
 -834.24669;147.90852;816.28839;,
 834.24669;147.90852;816.28829;,
 834.24669;-230.73799;816.28829;,
 -834.24669;-230.73799;816.28839;,
 1415.46360;474.38336;1401.34660;,
 834.24669;147.90852;816.28829;,
 -834.24669;147.90852;816.28839;,
 -1415.46360;474.38336;1401.34660;,
 964.32453;285.50535;-63.09441;,
 1092.20617;285.50535;-63.09441;,
 1092.20617;157.62483;-63.09441;,
 926.84269;157.62483;-63.09441;,
 1092.20617;285.50535;64.78600;,
 964.32453;285.50535;64.78600;,
 926.84269;157.62483;64.78600;,
 1092.20617;157.62483;64.78600;,
 964.32453;285.50535;64.78600;,
 964.32453;285.50535;-63.09441;,
 926.84269;157.62483;-63.09441;,
 926.84269;157.62483;64.78600;,
 1092.20617;285.50535;64.78600;,
 1092.20617;285.50535;-63.09441;,
 964.32453;285.50535;-63.09441;,
 -970.24630;285.50535;-63.09441;,
 -933.84415;157.62483;-63.09441;,
 -1098.12834;157.62483;-63.09441;,
 -1098.12834;285.50535;-63.09441;,
 -1098.12834;285.50535;64.78600;,
 -1098.12834;157.62483;64.78600;,
 -933.84415;157.62483;64.78600;,
 -970.24630;285.50535;64.78600;,
 -970.24630;285.50535;64.78600;,
 -933.84415;157.62483;64.78600;,
 -933.84415;157.62483;-63.09441;,
 -970.24630;285.50535;-63.09441;,
 -970.24630;285.50535;-63.09441;,
 -1098.12834;285.50535;-63.09441;,
 -1098.12834;285.50535;64.78600;,
 -79.31945;286.17510;948.34093;,
 48.56089;286.17510;948.34093;,
 48.56089;158.29441;902.14913;,
 -79.31945;158.29441;902.14913;,
 48.56089;286.17510;948.34093;,
 48.56089;286.17510;1076.22189;,
 48.56089;158.29441;1076.22189;,
 48.56089;158.29441;902.14913;,
 -79.31945;286.17510;1076.22189;,
 -79.31945;286.17510;948.34093;,
 -79.31945;158.29441;902.14913;,
 -79.31945;158.29441;1076.22189;,
 48.56089;286.17510;948.34093;,
 -79.31945;286.17510;948.34093;,
 48.56089;286.17510;-1069.49806;,
 48.56089;286.17510;-941.61896;,
 48.56089;163.99363;-889.63810;,
 48.56089;158.29441;-1069.49806;,
 48.56089;286.17510;-941.61896;,
 -79.31945;286.17510;-941.61896;,
 -79.31945;163.99363;-889.63810;,
 48.56089;163.99363;-889.63810;,
 -79.31945;286.17510;-941.61896;,
 -79.31945;286.17510;-1069.49806;,
 -79.31945;158.29441;-1069.49806;,
 -79.31945;163.99363;-889.63810;,
 48.56089;286.17510;-1069.49806;,
 -79.31945;286.17510;-1069.49806;;
 
 27;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,56,57,58;,
 4;59,60,61,62;,
 4;63,64,65,66;,
 4;67,68,69,70;,
 4;67,71,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;82,79,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;96,89,100,101;;
 
 MeshMaterialList {
  11;
  27;
  9,
  10,
  0,
  9,
  10,
  2,
  9,
  5,
  1,
  9,
  3,
  5,
  5,
  7,
  5,
  5,
  5,
  4,
  5,
  8,
  5,
  5,
  5,
  5,
  6,
  5,
  5;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/STAGE/audience.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/STAGE/audience.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/STAGE/audience.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/STAGE/audience.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/STAGE/doorway.png";
   }
  }
  Material {
   0.000000;0.702400;0.800000;1.000000;;
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
    "data/TEXTURE/STAGE/doorway.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/STAGE/doorway.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/STAGE/doorway.png";
   }
  }
  Material {
   0.000000;0.172800;0.298400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  25;
  1.000000;0.000000;0.000000;,
  0.485699;0.874126;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.483158;0.875533;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.875731;0.482799;,
  -0.000000;0.873242;-0.487287;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.959629;0.281268;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  0.961792;0.273781;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.339727;-0.940524;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.391483;0.920185;,
  0.000000;1.000000;0.000000;;
  27;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;6,6,6,6;,
  4;8,8,8,8;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;21,21,21,21;,
  4;24,24,24,24;;
 }
 MeshTextureCoords {
  102;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  4.215609;3.285776;,
  1.844621;3.444886;,
  -3.194778;1.391260;,
  -4.463620;-0.251131;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  4.287983;0.886978;,
  -1.645300;-1.645200;,
  -1.137481;-0.409254;,
  2.307548;1.060998;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  -3.482551;-0.180211;,
  3.794561;-0.014215;,
  2.261650;1.244284;,
  -2.006002;1.146936;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  -3.003810;-0.292123;,
  -1.182748;0.613989;,
  2.843394;0.035753;,
  3.827332;-1.273214;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
