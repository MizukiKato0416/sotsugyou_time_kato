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
 -177.47029;243.57159;-99.27499;,
 -259.62547;260.39161;-134.34992;,
 -259.62547;317.21541;-134.34992;,
 -128.72433;317.21541;-99.27499;,
 -259.62547;317.21541;23.42444;,
 -195.80179;317.21541;16.90663;,
 243.35147;292.34664;-344.74539;,
 311.33255;448.07144;-458.55689;,
 374.39481;274.80892;-458.55689;,
 -24.74055;129.53549;-344.74539;,
 374.39481;274.80892;53.39232;,
 179.78814;203.97744;478.70631;,
 -292.51497;-376.95528;-217.27093;,
 -224.53367;-522.88023;-343.40274;,
 113.70434;-376.34173;-117.18244;,
 -167.36253;-298.48995;-210.60921;,
 -161.47141;14.92339;-289.74417;,
 -356.07811;-47.74733;-202.58098;;
 
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
  0.751335;-0.497320;0.433783;,
  -1.000000;0.000000;0.000000;,
  -0.167539;-0.897533;0.407878;,
  -0.613534;0.258296;-0.746230;,
  0.342021;-0.939692;-0.000000;,
  -0.516301;0.846685;0.128680;,
  -0.518382;0.853591;0.051589;,
  0.939693;0.342019;0.000000;,
  -0.511123;0.834702;0.205000;,
  0.000336;-0.138308;0.990389;,
  -0.007678;-0.107056;0.994223;,
  0.012960;0.098521;0.995051;,
  -0.047494;-0.499731;0.864877;,
  -0.036006;-0.282251;0.958665;,
  0.048116;0.243677;0.968662;,
  0.550208;0.018776;-0.834817;,
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
