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
 20;
 -1084.20168;0.00000;23811.60192;,
 1077.81847;0.00000;23811.60192;,
 1077.81847;0.00000;-23811.60192;,
 -1084.20168;0.00000;-23811.60192;,
 -1074.24269;45.56056;-23808.51442;,
 -952.08478;45.56056;-23808.51442;,
 -952.08478;-0.52984;-23808.51442;,
 -1074.24269;-0.52984;-23808.51442;,
 -952.08478;45.56056;23808.51442;,
 -952.08478;-0.52984;23808.51442;,
 -1074.24269;45.56056;23808.51442;,
 -1074.24269;-0.52984;23808.51442;,
 965.60226;45.56056;-23808.51442;,
 1087.76007;45.56056;-23808.51442;,
 1087.76007;-0.52984;-23808.51442;,
 965.60226;-0.52984;-23808.51442;,
 1087.76007;45.56056;23808.51442;,
 1087.76007;-0.52984;23808.51442;,
 965.60226;45.56056;23808.51442;,
 965.60226;-0.52984;23808.51442;;
 
 13;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;8,10,11,9;,
 4;10,4,7,11;,
 4;10,8,5,4;,
 4;7,6,9,11;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;16,18,19,17;,
 4;18,12,15,19;,
 4;18,16,13,12;,
 4;15,14,17,19;;
 
 MeshMaterialList {
  2;
  13;
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/road.jpg";
   }
  }
  Material {
   0.630588;0.630588;0.630588;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/rock.jpg";
   }
  }
 }
 MeshNormals {
  13;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  13;
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
  4;12,12,12,12;;
 }
 MeshTextureCoords {
  20;
  -0.051392;-11.609855;,
  1.048146;-11.609855;,
  1.048146;12.609855;,
  -0.051392;12.609855;,
  -1.632005;47.751781;,
  -1.389564;47.751781;,
  -1.389564;47.751781;,
  -1.632005;47.751781;,
  -1.389564;-46.751781;,
  -1.389564;-46.751781;,
  -1.632005;-46.751781;,
  -1.632005;-46.751781;,
  2.416391;47.751781;,
  2.658833;47.751781;,
  2.658833;47.751781;,
  2.416391;47.751781;,
  2.658833;-46.751781;,
  2.658833;-46.751781;,
  2.416391;-46.751781;,
  2.416391;-46.751781;;
 }
}
