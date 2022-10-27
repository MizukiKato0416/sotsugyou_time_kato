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
 48;
 -176.56836;-161.24389;-6.85911;,
 3.01929;-238.95669;-84.57189;,
 -29.42393;-181.05114;71.23902;,
 -176.56836;-56.84764;-14.93674;,
 182.60699;-135.75288;18.63209;,
 182.60699;-59.66267;94.72208;,
 3.01929;70.14009;112.05088;,
 -136.54108;83.69989;110.60647;,
 182.60699;37.77874;144.41214;,
 182.60699;-135.75288;18.63209;,
 253.31673;-75.88312;-175.47400;,
 297.94102;13.90317;-85.68759;,
 182.60699;-59.66267;94.72208;,
 145.08469;-42.92403;-90.70117;,
 289.94371;82.29771;-131.00467;,
 182.60699;140.89079;41.30007;,
 182.60699;37.77874;144.41214;,
 182.60699;199.72191;-17.53113;,
 145.08469;-42.92403;-90.70117;,
 174.35672;-56.56155;-281.71939;,
 103.32013;174.21316;-192.88159;,
 289.94371;82.29771;-131.00467;,
 -47.40793;-4.18329;-258.28028;,
 -176.56836;224.52730;-129.03848;,
 3.01929;267.80962;-85.61876;,
 182.60699;199.72191;-17.53113;,
 -75.15311;267.87832;-85.68755;,
 -47.40793;-4.18329;-258.28028;,
 -99.50914;-99.66170;-172.97544;,
 -277.45025;13.90317;-85.68759;,
 -176.56836;224.52730;-129.03848;,
 -176.56836;-161.24389;-6.85911;,
 -176.56836;-56.84764;-14.93674;,
 -176.56836;140.89079;41.30007;,
 -75.15311;267.87832;-85.68755;,
 -136.54108;83.69989;110.60647;,
 132.17969;-223.82266;-223.94395;,
 -99.50914;-99.66170;-172.97544;,
 253.31673;-75.88312;-175.47400;,
 3.01929;-238.95669;-84.57189;,
 -176.56836;-161.24389;-6.85911;,
 182.60699;-135.75288;18.63209;,
 -176.56836;140.89079;41.30007;,
 3.01929;216.88994;117.29927;,
 182.60699;140.89079;41.30007;,
 -136.54108;83.69989;110.60647;,
 3.01929;70.14009;112.05088;,
 182.60699;37.77874;144.41214;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;10,13,14,11;,
 4;12,11,15,16;,
 4;11,14,17,15;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;21,20,24,25;,
 4;20,23,26,24;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;30,29,33,34;,
 4;29,32,35,33;,
 4;27,19,36,37;,
 4;19,13,38,36;,
 4;37,36,39,40;,
 4;36,38,41,39;,
 4;42,43,24,34;,
 4;43,44,17,24;,
 4;45,46,43,42;,
 4;46,47,44,43;;
 
 MeshMaterialList {
  1;
  24;
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
  40;
  -0.453224;-0.524205;0.720970;,
  0.167258;-0.816538;0.552531;,
  -0.546563;-0.373443;0.749540;,
  -0.165524;-0.540464;0.824924;,
  -0.508080;-0.109636;0.854304;,
  -0.146262;-0.018966;0.989064;,
  0.606373;-0.719492;0.338590;,
  0.730517;-0.646791;0.219103;,
  0.586594;-0.455241;0.669823;,
  0.920309;-0.004910;0.391160;,
  0.042973;0.036746;0.998400;,
  0.653436;0.453889;0.605810;,
  0.587334;0.183154;-0.788349;,
  0.812719;0.169395;-0.557489;,
  0.513264;0.348445;-0.784312;,
  0.800324;-0.122279;-0.586967;,
  0.640717;0.744741;0.186661;,
  0.183013;0.980574;-0.070583;,
  -0.351851;-0.036624;-0.935339;,
  -0.600306;-0.453289;-0.658910;,
  -0.255508;0.382806;-0.887793;,
  -0.760063;-0.323175;-0.563792;,
  -0.010940;0.743887;-0.668216;,
  -0.601458;0.482955;0.636398;,
  -0.415001;-0.557581;-0.718942;,
  0.021417;0.668959;0.742991;,
  0.418464;0.343481;-0.840779;,
  -0.024550;0.153193;-0.987891;,
  0.894453;0.078909;0.440144;,
  0.838452;0.376064;0.394429;,
  -0.201809;0.007845;-0.979394;,
  0.141339;0.707050;-0.692895;,
  -0.682891;-0.609915;-0.402075;,
  -0.827439;-0.492344;-0.270077;,
  -0.701418;0.639789;0.314138;,
  -0.826834;0.261782;0.497811;,
  -0.495865;0.802395;0.332084;,
  0.755141;0.446485;-0.480013;,
  -0.502736;-0.695684;-0.513109;,
  0.583195;-0.794905;0.167362;;
  24;
  4;0,1,3,2;,
  4;1,6,8,3;,
  4;2,3,5,4;,
  4;3,8,10,5;,
  4;6,7,9,8;,
  4;26,12,14,27;,
  4;8,9,11,28;,
  4;9,29,16,11;,
  4;12,13,15,14;,
  4;30,18,20,31;,
  4;14,31,17,16;,
  4;31,20,22,17;,
  4;18,19,21,20;,
  4;19,32,33,21;,
  4;34,35,23,36;,
  4;35,2,4,23;,
  4;18,30,24,19;,
  4;13,12,26,37;,
  4;19,24,38,32;,
  4;39,7,6,1;,
  4;23,25,17,36;,
  4;25,11,16,17;,
  4;4,5,25,23;,
  4;5,10,11,25;;
 }
 MeshTextureCoords {
  48;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
