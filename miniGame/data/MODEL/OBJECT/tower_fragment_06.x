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
 247.51128;-756.96017;678.94679;,
 -319.14610;-624.60440;-329.85059;,
 209.22403;-602.58780;-359.07364;,
 962.54845;-381.12945;53.78331;,
 335.92044;-158.72454;-189.82620;,
 212.76524;-199.12168;513.23663;,
 -1226.38664;-115.83606;270.35306;,
 -1508.58938;-420.55626;75.81044;,
 -1591.16555;-343.33338;603.80890;,
 -1021.04533;-505.16436;179.98339;,
 -1508.58938;-420.55626;75.81044;,
 -766.44777;-177.92005;-163.38919;,
 177.74628;-352.96758;-653.09249;,
 -585.00636;554.24327;-132.91277;,
 -492.60689;-232.87334;-674.43136;,
 -1039.20724;294.63462;-539.16485;;
 
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
  15;
  0.196029;-0.968853;-0.151316;,
  0.454902;0.741545;-0.493129;,
  0.210398;0.603564;-0.769054;,
  0.549862;0.269135;0.790707;,
  -0.066708;0.372057;-0.925810;,
  -0.816163;0.519649;0.252672;,
  -0.029765;0.840558;0.540903;,
  -0.193157;-0.974714;0.112349;,
  0.252852;0.343320;-0.904543;,
  0.434303;-0.144635;0.889079;,
  -0.467400;-0.870011;-0.156901;,
  0.186129;0.498696;-0.846556;,
  0.089623;0.333516;-0.938475;,
  0.274251;0.641412;-0.716503;,
  -0.704516;0.145678;0.694575;;
  13;
  4;0,0,0,0;,
  4;2,1,1,2;,
  3;3,3,3;,
  3;4,2,2;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  3;7,7,7;,
  3;8,8,8;,
  3;9,9,9;,
  4;10,10,10,10;,
  3;11,12,11;,
  3;13,11,11;,
  3;14,14,14;;
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
