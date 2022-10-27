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
 12;
 -34.78336;-14.82505;-122.60713;,
 -74.55793;-23.73931;-92.73839;,
 -74.55793;27.28107;-76.98450;,
 35.04701;17.55685;-75.53121;,
 -74.55793;-16.46045;-70.44730;,
 22.48656;-14.65344;-70.71737;,
 10.33646;33.44548;28.28515;,
 -26.43622;24.37640;10.97308;,
 -81.00126;12.73424;46.15327;,
 -34.38392;5.00541;84.92976;,
 0.24999;-7.51853;-3.84441;,
 -1.00321;-32.77825;21.61565;;
 
 10;
 4;0,1,2,3;,
 4;4,5,3,2;,
 3;0,3,5;,
 3;1,4,2;,
 4;5,4,1,0;,
 4;6,7,8,9;,
 4;10,11,9,8;,
 3;6,9,11;,
 3;7,10,8;,
 4;11,10,7,6;;
 
 MeshMaterialList {
  1;
  10;
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
  10;
  -0.301049;0.555477;-0.775122;,
  0.000000;0.147809;0.989016;,
  0.629731;-0.349263;-0.693869;,
  -1.000000;0.000000;0.000000;,
  0.072121;-0.993149;0.091941;,
  -0.187520;0.954960;0.229975;,
  -0.526869;-0.831735;-0.175004;,
  0.815029;-0.194527;0.545790;,
  -0.532985;-0.053649;-0.844422;,
  0.776197;0.259550;-0.574589;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  3;2,2,2;,
  3;3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  3;7,7,7;,
  3;8,8,8;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  12;
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
