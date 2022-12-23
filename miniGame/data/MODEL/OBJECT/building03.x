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
 98;
 -830.10109;4450.08874;-830.10109;,
 830.10109;4450.08874;-830.10109;,
 830.40626;978.34191;-828.61876;,
 -830.40626;978.34191;-828.61876;,
 830.10109;4450.08874;-830.10109;,
 830.10109;4450.08874;830.10109;,
 828.69122;978.34191;829.53615;,
 830.40626;978.34191;-828.61876;,
 830.10109;4450.08874;830.10109;,
 -830.10109;4450.08874;830.10109;,
 -828.69122;978.34191;829.53615;,
 828.69122;978.34191;829.53615;,
 -830.10109;4450.08874;830.10109;,
 -830.10109;4450.08874;-830.10109;,
 -830.40626;978.34191;-828.61876;,
 -828.69122;978.34191;829.53615;,
 -830.10109;4450.08874;830.10109;,
 830.10109;4450.08874;830.10109;,
 830.10109;4450.08874;-830.10109;,
 -830.10109;4450.08874;-830.10109;,
 -830.40626;978.34191;-828.61876;,
 830.40626;978.34191;-828.61876;,
 828.69122;978.34191;829.53615;,
 -828.69122;978.34191;829.53615;,
 469.54024;978.34191;-828.61876;,
 830.40626;978.34191;-828.61876;,
 830.40626;-0.00026;-828.61876;,
 469.54024;-0.00026;-828.61876;,
 830.40626;978.34191;-828.61876;,
 830.40626;978.34191;-467.75411;,
 830.40626;-0.00026;-467.75411;,
 830.40626;-0.00026;-828.61876;,
 830.40626;978.34191;-467.75411;,
 469.54024;978.34191;-467.75411;,
 469.54024;-0.00026;-467.75411;,
 830.40626;-0.00026;-467.75411;,
 469.54024;978.34191;-467.75411;,
 469.54024;978.34191;-828.61876;,
 469.54024;-0.00026;-828.61876;,
 469.54024;-0.00026;-467.75411;,
 469.54024;-0.00026;-828.61876;,
 830.40626;-0.00026;-828.61876;,
 -469.54024;978.34191;-828.61876;,
 -469.54024;-0.00026;-828.61876;,
 -830.40626;-0.00026;-828.61876;,
 -830.40626;978.34191;-828.61876;,
 -830.40626;978.34191;-828.61876;,
 -830.40626;-0.00026;-828.61876;,
 -830.40626;-0.00026;-467.75411;,
 -830.40626;978.34191;-467.75411;,
 -830.40626;978.34191;-467.75411;,
 -830.40626;-0.00026;-467.75411;,
 -469.54024;-0.00026;-467.75411;,
 -469.54024;978.34191;-467.75411;,
 -469.54024;978.34191;-467.75411;,
 -469.54024;-0.00026;-467.75411;,
 -469.54024;-0.00026;-828.61876;,
 -469.54024;978.34191;-828.61876;,
 -469.54024;-0.00026;-828.61876;,
 -830.40626;-0.00026;-828.61876;,
 467.82545;978.34191;468.67017;,
 828.69122;978.34191;468.67017;,
 828.69122;-0.00026;468.67017;,
 467.82545;-0.00026;468.67017;,
 828.69122;978.34191;468.67017;,
 828.69122;978.34191;829.53615;,
 828.69122;-0.00026;829.53615;,
 828.69122;-0.00026;468.67017;,
 828.69122;978.34191;829.53615;,
 467.82545;978.34191;829.53615;,
 467.82545;-0.00026;829.53615;,
 828.69122;-0.00026;829.53615;,
 467.82545;978.34191;829.53615;,
 467.82545;978.34191;468.67017;,
 467.82545;-0.00026;468.67017;,
 467.82545;-0.00026;829.53615;,
 467.82545;-0.00026;468.67017;,
 828.69122;-0.00026;468.67017;,
 -465.06173;980.32160;476.34371;,
 -465.06173;1.97787;476.34371;,
 -828.69122;-0.00026;468.67017;,
 -828.69122;978.34191;468.67017;,
 -828.69122;978.34191;468.67017;,
 -828.69122;-0.00026;468.67017;,
 -828.69122;-0.00026;829.53615;,
 -828.69122;978.34191;829.53615;,
 -828.69122;978.34191;829.53615;,
 -828.69122;-0.00026;829.53615;,
 -467.82545;-0.00026;829.53615;,
 -467.82545;978.34191;829.53615;,
 -467.82545;978.34191;829.53615;,
 -467.82545;-0.00026;829.53615;,
 -465.06173;1.97787;476.34371;,
 -465.06173;980.32160;476.34371;,
 -465.06173;1.97787;476.34371;,
 -828.69122;-0.00026;468.67017;,
 -469.54024;-0.00026;-467.75411;,
 469.54024;-0.00026;-467.75411;;
 
 31;
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
 4;40,41,30,39;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,55,48,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,66,75;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,91,84,95;,
 4;54,33,34,55;,
 4;36,73,74,39;,
 4;60,93,92,63;,
 4;78,53,52,79;,
 4;96,97,74,79;;
 
 MeshMaterialList {
  5;
  31;
  0,
  1,
  0,
  1,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/building03a.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/building03a.jpg";
   }
  }
  Material {
   0.348000;0.728000;0.800000;0.800000;;
   5.000000;
   0.530000;0.530000;0.530000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/building03b.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/building03b.jpg";
   }
  }
 }
 MeshNormals {
  22;
  0.000000;-0.000427;-1.000000;,
  0.000000;-0.000213;-1.000000;,
  1.000000;-0.000159;0.000517;,
  1.000000;-0.000079;0.000259;,
  0.000000;-0.000163;1.000000;,
  0.000000;-0.000081;1.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.021098;0.000000;-0.999777;,
  -1.000000;-0.000159;0.000517;,
  -1.000000;-0.000079;0.000259;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000526;-1.000000;0.000526;,
  0.999969;0.000000;0.007825;,
  0.000834;-0.999999;-0.000874;,
  0.002720;-0.999992;-0.002800;,
  0.999998;0.000000;0.001831;,
  0.008225;0.000000;0.999966;,
  -0.999989;0.000000;0.004744;;
  31;
  4;0,0,1,1;,
  4;2,2,3,3;,
  4;4,4,5,5;,
  4;11,11,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;6,1,6,6;,
  4;3,7,7,7;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;14,14,14,15;,
  4;6,6,6,1;,
  4;12,8,8,8;,
  4;9,9,9,9;,
  4;7,7,7,7;,
  4;14,15,14,14;,
  4;6,6,6,6;,
  4;7,3,7,7;,
  4;5,9,9,9;,
  4;8,8,8,8;,
  4;15,14,14,14;,
  4;10,10,10,10;,
  4;8,8,8,12;,
  4;5,9,9,9;,
  4;16,16,16,16;,
  4;17,18,18,18;,
  4;6,6,6,6;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;15,15,15,17;;
 }
 MeshTextureCoords {
  98;
  -0.702321;-5.429876;,
  1.703298;-5.429876;,
  1.703741;-0.620156;,
  -0.702764;-0.620156;,
  -0.714870;-5.432238;,
  1.714870;-5.432238;,
  1.714043;-0.622516;,
  -0.712701;-0.622516;,
  1.703298;-5.429876;,
  -0.702321;-5.429876;,
  -0.700279;-0.620156;,
  1.701255;-0.620156;,
  1.714870;-5.432238;,
  -0.714870;-5.432238;,
  -0.712701;-0.622516;,
  1.714043;-0.622516;,
  -20.040062;17.248135;,
  21.047951;17.241707;,
  21.040062;-16.247667;,
  -20.047951;-16.241238;,
  -20.055496;-16.211336;,
  21.047623;-16.217768;,
  21.013056;17.230316;,
  -20.005173;17.236734;,
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
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}