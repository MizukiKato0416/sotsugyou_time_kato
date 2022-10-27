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
 16;
 9.91861;294.63462;-284.04258;,
 -1.11711;244.10782;293.49024;,
 180.32423;231.98965;323.96666;,
 624.82774;104.20481;-325.11116;,
 117.23432;-352.96758;-196.21304;,
 -125.52595;-232.87334;-419.30909;,
 -227.77388;783.81730;-434.91124;,
 -509.97677;-112.14932;75.81044;,
 -592.55294;-34.92644;603.80890;,
 -22.43259;-196.75733;543.50152;,
 -509.97677;-112.14932;75.81044;,
 -766.44777;-177.92005;-163.38919;,
 -648.09601;-352.96758;-653.09249;,
 -585.00636;231.98965;-132.91277;,
 -890.85656;-232.87334;-674.43136;,
 -1047.95324;294.63462;-539.16485;;
 
 13;
 4;0,1,2,3;,
 4;4,5,3,2;,
 3;0,3,5;,
 3;1,4,2;,
 4;5,4,1,0;,
 4;6,7,8,9;,
 3;9,8,10;,
 3;9,10,6;,
 3;11,12,13;,
 4;14,12,11,15;,
 3;12,14,15;,
 3;13,12,15;,
 3;15,11,13;;
 
 MeshMaterialList {
  1;
  13;
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
   TextureFilename {
    "data/TEXTURE/MESH/towerwall.png";
   }
  }
 }
 MeshNormals {
  14;
  0.175664;0.983073;0.052056;,
  0.649136;-0.752356;-0.112175;,
  0.011335;0.245641;-0.969294;,
  -0.168298;-0.644843;0.745556;,
  -0.917389;-0.099769;0.385285;,
  -0.166735;0.925097;0.341168;,
  -0.261966;-0.959942;0.099427;,
  0.532222;-0.539528;-0.652418;,
  0.847374;-0.400962;0.348120;,
  -0.723991;-0.644619;0.245566;,
  0.437252;0.410728;-0.800071;,
  0.232520;0.305980;-0.923207;,
  0.612228;0.487526;-0.622491;,
  -0.626084;0.221544;0.747621;;
  13;
  4;0,0,0,0;,
  4;1,1,1,1;,
  3;2,2,2;,
  3;3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  3;6,6,6;,
  3;7,7,7;,
  3;8,8,8;,
  4;9,9,9,9;,
  3;10,11,10;,
  3;12,10,10;,
  3;13,13,13;;
 }
 MeshTextureCoords {
  16;
  0.083330;0.321690;,
  0.000000;0.464230;,
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.025110;0.000000;,
  0.061980;0.000000;,
  0.025110;0.000000;,
  0.061980;0.000000;,
  0.083330;0.000000;,
  0.000000;0.000000;,
  0.083330;0.321690;,
  0.000000;0.464230;,
  0.025110;0.000000;,
  0.000000;0.000000;,
  0.061980;0.000000;,
  0.083330;0.321690;;
 }
}
