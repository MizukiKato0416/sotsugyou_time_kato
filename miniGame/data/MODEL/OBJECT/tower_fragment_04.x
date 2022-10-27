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
 -27.51503;10.94312;-8.30445;,
 -36.33523;13.69452;-14.04187;,
 -36.33523;22.98950;-14.04187;,
 -14.92293;22.98950;-8.30445;,
 -36.33523;22.98950;11.76621;,
 -25.89518;22.98950;10.70006;,
 15.81153;-14.82505;-59.70485;,
 0.69636;24.92664;-29.83610;,
 0.69636;27.28107;-14.08221;,
 10.69913;17.55685;-12.62892;,
 0.69636;-16.46045;-7.54501;,
 9.55284;-14.65344;-7.81508;;
 
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
    "C:\\Users\\student\\Downloads\\stone_wall_diff_1k.png";
   }
  }
 }
 MeshNormals {
  13;
  0.405984;-0.133346;-0.904100;,
  0.000000;1.000000;0.000000;,
  0.240548;-0.861220;0.447701;,
  0.642030;-0.671116;0.370676;,
  -1.000000;0.000000;0.000000;,
  -0.209828;-0.876272;0.433727;,
  0.768659;0.612469;-0.184514;,
  0.946820;0.319876;-0.034796;,
  0.000000;0.147809;0.989016;,
  0.992647;-0.017424;0.119786;,
  -0.888652;-0.276495;-0.365853;,
  -1.000000;0.000000;0.000000;,
  -0.579404;-0.491415;-0.650232;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  3;2,3,2;,
  3;4,4,4;,
  4;2,5,5,2;,
  4;7,6,6,7;,
  4;8,8,8,8;,
  3;7,7,9;,
  3;10,10,11;,
  4;12,10,10,12;;
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
