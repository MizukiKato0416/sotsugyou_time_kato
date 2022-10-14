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
 42;
 -53.73000;20.93090;100.00000;,
 53.73000;189.60899;100.00000;,
 53.73000;189.60899;-100.00000;,
 -53.73000;20.93090;-100.00000;,
 62.96190;-20.08160;17.96440;,
 126.63260;167.59760;-8.91340;,
 -62.96180;230.62140;-17.96440;,
 -126.63250;42.94230;8.91340;,
 106.15770;71.03340;-86.93910;,
 92.13130;165.54820;88.76010;,
 -106.15770;139.50661;86.93910;,
 -92.13130;44.99170;-88.76010;,
 6.74170;-19.48590;66.26070;,
 -126.15190;129.80180;59.02360;,
 -6.74140;230.02589;-66.26090;,
 126.15260;80.73820;-59.02390;,
 -53.73000;227.51550;-46.57350;,
 53.73000;79.98630;-128.35040;,
 53.73000;-16.97560;46.57350;,
 -53.73000;130.55360;128.35040;,
 102.86540;202.30890;1.47020;,
 41.20940;63.53620;-128.68600;,
 -102.86540;8.23100;-1.47030;,
 -41.20940;147.00369;128.68590;,
 0.00000;56.95150;-22.14880;,
 13.00250;56.95150;-22.14880;,
 13.00250;-4.07380;-22.14880;,
 0.00000;-4.07380;-22.14880;,
 13.00250;56.95150;-22.14880;,
 13.00250;56.95150;-9.14630;,
 13.00250;-4.07380;-9.14630;,
 13.00250;-4.07380;-22.14880;,
 13.00250;56.95150;-9.14630;,
 0.00000;56.95150;-9.14630;,
 0.00000;-4.07380;-9.14630;,
 13.00250;-4.07380;-9.14630;,
 0.00000;56.95150;-9.14630;,
 0.00000;56.95150;-22.14880;,
 0.00000;-4.07380;-22.14880;,
 0.00000;-4.07380;-9.14630;,
 13.00250;56.95150;-22.14880;,
 0.00000;56.95150;-22.14880;;
 
 17;
 4;0,1,2,3;,
 4;3,2,1,0;,
 4;4,5,6,7;,
 4;7,6,5,4;,
 4;8,9,10,11;,
 4;11,10,9,8;,
 4;12,13,14,15;,
 4;15,14,13,12;,
 4;16,17,18,19;,
 4;19,18,17,16;,
 4;20,21,22,23;,
 4;23,22,21,20;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;36,29,40,41;;
 
 MeshMaterialList {
  2;
  17;
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
  1;;
  Material {
   0.800000;0.709020;0.730980;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MESH\\leaf01.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MESH\\wood.jpg";
   }
  }
 }
 MeshNormals {
  17;
  -0.843391;0.537300;0.000000;,
  0.843391;-0.537300;-0.000000;,
  -0.000119;0.141804;0.989895;,
  0.000119;-0.141804;-0.989895;,
  0.110085;-0.871619;0.477663;,
  -0.110085;0.871619;-0.477663;,
  -0.449453;-0.437843;-0.778643;,
  0.449453;0.437843;0.778643;,
  -0.843391;-0.469933;-0.260488;,
  0.843391;0.469933;0.260488;,
  -0.621309;0.664896;-0.414594;,
  0.621309;-0.664896;0.414594;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  17;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;;
 }
 MeshTextureCoords {
  42;
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}