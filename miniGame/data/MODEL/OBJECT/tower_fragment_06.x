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
 18;
 -22.77116;10.66660;-8.63350;,
 -36.82674;13.54431;-14.63431;,
 -36.82674;23.26602;-14.63431;,
 -14.43141;23.26602;-8.63350;,
 -36.82674;23.26602;12.35864;,
 -25.90742;23.26602;11.24353;,
 49.22549;19.01138;-50.63000;,
 60.85608;45.65367;-70.10154;,
 71.64514;16.01090;-70.10154;,
 3.35873;-8.84334;-50.63000;,
 71.64514;16.01090;17.48571;,
 38.35070;3.89266;90.25090;,
 -42.45366;-95.49671;-28.82093;,
 -30.82306;-120.46243;-50.40028;,
 27.04470;-95.39173;-11.69721;,
 -21.04187;-82.07238;-27.68120;,
 -20.03399;-28.45183;-41.22007;,
 -53.32844;-39.17391;-26.30768;;
 
 15;
 4;0,1,2,3;,
 4;4,5,3,2;,
 3;0,3,5;,
 3;1,4,2;,
 4;5,4,1,0;,
 4;6,7,8,9;,
 4;10,11,9,8;,
 3;6,9,11;,
 3;7,10,8;,
 4;11,10,7,6;,
 4;12,13,14,15;,
 4;16,17,15,14;,
 3;12,15,17;,
 3;13,16,14;,
 4;17,16,13,12;;
 
 MeshMaterialList {
  1;
  15;
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
   TextureFilename {
    "data/TEXTURE/MESH/towerwall.png";
   }
  }
 }
 MeshNormals {
  19;
  0.325856;-0.084945;-0.941596;,
  0.000000;1.000000;0.000000;,
  0.751335;-0.497320;0.433784;,
  -1.000000;0.000000;0.000000;,
  -0.167540;-0.897533;0.407877;,
  -0.613535;0.258295;-0.746230;,
  0.342021;-0.939692;-0.000000;,
  -0.516301;0.846685;0.128680;,
  -0.518383;0.853591;0.051589;,
  0.939693;0.342019;0.000000;,
  -0.511123;0.834703;0.205000;,
  0.000336;-0.138308;0.990389;,
  -0.007678;-0.107056;0.994223;,
  0.012960;0.098521;0.995051;,
  -0.047493;-0.499731;0.864878;,
  -0.036006;-0.282251;0.958665;,
  0.048116;0.243677;0.968662;,
  0.550207;0.018776;-0.834817;,
  -0.614707;0.060110;-0.786462;;
  15;
  4;0,0,0,0;,
  4;1,1,1,1;,
  3;2,2,2;,
  3;3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  3;7,8,7;,
  3;9,9,9;,
  4;7,10,10,7;,
  4;15,14,11,12;,
  4;16,13,12,11;,
  3;15,12,13;,
  3;17,17,17;,
  4;18,18,18,18;;
 }
 MeshTextureCoords {
  18;
  0.083330;0.321690;,
  0.000000;0.464230;,
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.025110;0.000000;,
  0.061980;0.000000;,
  0.083330;0.321690;,
  0.000000;0.464230;,
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.025110;0.000000;,
  0.061980;0.000000;,
  0.083330;0.321690;,
  0.000000;0.464230;,
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.025110;0.000000;,
  0.061980;0.000000;;
 }
}
