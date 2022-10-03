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
 34;
 0.00000;0.00000;0.00000;,
 5.43058;0.00000;-5.43058;,
 0.00000;0.00000;-7.68000;,
 7.68000;0.00000;0.00000;,
 5.43058;0.00000;5.43058;,
 0.00000;0.00000;7.68000;,
 -5.43058;0.00000;5.43058;,
 -7.68000;0.00000;0.00000;,
 -5.43058;0.00000;-5.43058;,
 6.78823;-6.91198;-6.78823;,
 0.00000;-6.91198;-9.60000;,
 9.60000;-6.91198;0.00000;,
 6.78823;-6.91198;6.78823;,
 0.00000;-6.91198;9.60000;,
 -6.78823;-6.91198;6.78822;,
 -9.60000;-6.91198;0.00000;,
 -6.78823;-6.91198;-6.78822;,
 11.73006;-59.69203;-11.73006;,
 0.00000;-59.69203;-16.58880;,
 16.58880;-59.69203;0.00000;,
 11.73006;-59.69203;11.73006;,
 0.00000;-59.69203;16.58880;,
 -11.73006;-59.69203;11.73005;,
 -16.58880;-59.69203;0.00000;,
 -11.73006;-59.69203;-11.73005;,
 9.38404;-71.63597;-9.38404;,
 0.00000;-71.63597;-13.27104;,
 13.27104;-71.63597;0.00000;,
 9.38404;-71.63597;9.38404;,
 0.00000;-71.63597;13.27104;,
 -9.38405;-71.63597;9.38404;,
 -13.27104;-71.63597;0.00000;,
 -9.38405;-71.63597;-9.38404;,
 0.00000;-71.63597;-0.00000;;
 
 40;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 3;26,25,33;,
 3;25,27,33;,
 3;27,28,33;,
 3;28,29,33;,
 3;29,30,33;,
 3;30,31,33;,
 3;31,32,33;,
 3;32,26,33;;
 
 MeshMaterialList {
  1;
  40;
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
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  26;
  0.000000;1.000000;0.000000;,
  0.370671;0.248579;-0.894881;,
  0.894881;0.248579;-0.370671;,
  0.894881;0.248579;0.370671;,
  0.370671;0.248579;0.894881;,
  -0.370672;0.248579;0.894880;,
  -0.894880;0.248579;0.370671;,
  -0.894880;0.248579;-0.370671;,
  0.379851;0.121429;-0.917043;,
  0.917043;0.121429;-0.379851;,
  0.917043;0.121429;0.379851;,
  0.379851;0.121429;0.917043;,
  -0.379852;0.121429;0.917043;,
  -0.917043;0.121429;0.379851;,
  -0.917043;0.121429;-0.379851;,
  0.370672;-0.248578;-0.894881;,
  0.894881;-0.248578;-0.370672;,
  0.894881;-0.248578;0.370672;,
  0.370672;-0.248578;0.894881;,
  -0.370672;-0.248578;0.894881;,
  -0.894881;-0.248578;0.370671;,
  -0.894881;-0.248578;-0.370671;,
  0.000000;-1.000000;-0.000000;,
  -0.370672;0.248579;-0.894880;,
  -0.379852;0.121429;-0.917043;,
  -0.370672;-0.248578;-0.894881;;
  40;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;23,23,23,23;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;24,24,24,24;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;25,25,25,25;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;;
 }
 MeshTextureCoords {
  34;
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
  0.000000;0.000000;;
 }
}
