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
 157;
 1.55603;441.39376;11.26634;,
 44.97690;426.08497;-73.05811;,
 1.55603;426.08497;-83.76048;,
 78.45046;426.08497;-43.40305;,
 94.30808;426.08497;-1.58889;,
 88.91775;426.08497;42.80520;,
 63.51403;426.08497;79.60942;,
 23.91618;426.08497;100.39147;,
 -20.80413;426.08497;100.39147;,
 -60.40170;426.08497;79.60942;,
 -85.80566;426.08497;42.80520;,
 -91.19624;426.08497;-1.58889;,
 -75.33806;426.08497;-43.40305;,
 -41.86458;426.08497;-73.05811;,
 96.79921;399.44666;-171.33484;,
 1.55603;399.44666;-194.81006;,
 170.22334;399.44666;-106.28644;,
 205.00774;399.44666;-14.56749;,
 193.18410;399.44666;82.81102;,
 137.46043;399.44666;163.54040;,
 50.60289;399.44666;209.12708;,
 -47.49053;399.44666;209.12708;,
 -134.34849;399.44666;163.54040;,
 -190.07191;399.44666;82.81102;,
 -201.89621;399.44666;-14.56749;,
 -167.11103;399.44666;-106.28644;,
 -93.68697;399.44666;-171.33484;,
 138.03568;362.78528;-249.71490;,
 1.55603;362.78528;-283.35386;,
 243.24949;362.78528;-156.50331;,
 293.09397;362.78528;-25.07350;,
 276.15061;362.78528;114.46597;,
 196.30190;362.78528;230.14827;,
 71.83808;362.78528;295.47185;,
 -68.72627;362.78528;295.47185;,
 -193.18939;362.78528;230.14827;,
 -273.03929;362.78528;114.46597;,
 -289.98233;362.78528;-25.07350;,
 -240.13775;362.78528;-156.50331;,
 -134.92340;362.78528;-249.71490;,
 177.37847;331.14827;-324.46006;,
 1.55603;331.14827;-367.79651;,
 312.92166;331.14827;-204.37884;,
 377.13533;331.14827;-35.06240;,
 355.30772;331.14827;144.70126;,
 252.44009;331.14827;293.73130;,
 92.09801;331.14827;377.88448;,
 -88.98607;331.14827;377.88448;,
 -249.32859;331.14827;293.73155;,
 -352.19539;331.14827;144.70126;,
 -374.02320;331.14827;-35.06240;,
 -309.80943;331.14827;-204.37884;,
 -174.26609;331.14827;-324.46033;,
 209.92898;299.21932;-386.36780;,
 1.55603;299.89739;-437.72808;,
 370.56707;299.21932;-244.05572;,
 446.66822;299.21932;-43.39277;,
 420.79996;299.21932;169.65207;,
 298.88763;299.21932;346.27198;,
 108.86085;299.21932;446.00670;,
 -105.74845;299.21932;446.00670;,
 -295.77561;299.89739;346.27198;,
 -417.68775;299.89739;169.65207;,
 -443.55582;299.89739;-43.39277;,
 -367.45491;299.89739;-244.05572;,
 -206.81721;299.89739;-386.36898;,
 242.35081;257.70579;-447.90123;,
 1.55603;257.70579;-507.25152;,
 427.98170;257.70579;-283.44642;,
 515.92545;257.70579;-51.56106;,
 486.03067;257.70579;194.63169;,
 345.15054;257.70579;398.73243;,
 125.55650;257.70579;513.98438;,
 -122.44415;257.70579;513.98438;,
 -342.03860;257.70579;398.73243;,
 -482.91925;257.70579;194.63189;,
 -512.81265;257.70579;-51.56106;,
 -424.86988;257.70579;-283.44642;,
 -239.23838;257.70579;-447.90123;,
 284.40166;224.41463;-490.81563;,
 -17.51477;224.41463;-565.23267;,
 484.63477;226.00984;-317.52684;,
 586.40079;209.73579;-51.96859;,
 552.81407;209.73579;224.63802;,
 394.53023;209.73579;453.95245;,
 147.80799;209.73579;583.44293;,
 -130.83059;209.73579;583.44293;,
 -377.55235;209.73579;453.95245;,
 -535.83726;209.73579;224.63802;,
 -586.84571;220.99571;-53.76912;,
 -476.57969;220.99571;-344.51431;,
 -243.82825;220.99571;-550.71456;,
 305.06033;183.64451;-571.95343;,
 0.00000;183.64451;-647.14381;,
 540.23648;183.64451;-363.60613;,
 651.64972;183.64451;-69.83268;,
 613.77848;183.64451;242.06726;,
 435.29717;183.64451;500.64093;,
 157.09535;183.64451;646.65357;,
 -157.09535;183.64451;646.65357;,
 -435.29717;183.64451;500.64093;,
 -613.77848;183.64451;242.06726;,
 -651.64972;183.64451;-69.83298;,
 -540.23648;183.64451;-363.60613;,
 -305.06028;183.64451;-571.95343;,
 343.12862;137.76218;-643.63438;,
 0.00000;137.76218;-728.20978;,
 607.65123;137.76218;-409.28792;,
 732.96705;137.76218;-78.85542;,
 690.37013;137.76218;271.96560;,
 489.61719;137.76218;562.80553;,
 176.69921;137.76218;727.03868;,
 -194.98954;142.20894;804.63014;,
 -535.60484;146.87195;592.35377;,
 -690.37013;137.76218;271.96607;,
 -732.96705;137.76218;-78.85542;,
 -607.65079;137.76218;-409.28836;,
 -343.12862;137.76218;-643.63551;,
 436.99464;72.29026;-819.66066;,
 0.00000;72.29026;-927.37033;,
 773.87931;72.29026;-521.20665;,
 933.47687;72.29026;-100.38101;,
 879.22550;72.29026;346.40962;,
 623.55641;72.29026;716.81354;,
 225.03653;72.29026;925.97179;,
 -225.03653;72.29026;925.97179;,
 -623.55641;72.29026;716.81354;,
 -879.22550;72.29026;346.40994;,
 -933.47687;72.29026;-100.38151;,
 -773.87931;72.29026;-521.20679;,
 -436.99459;72.29026;-819.66066;,
 491.37525;36.17410;-921.44728;,
 0.00000;36.17410;-1042.55929;,
 870.18302;36.17410;-585.85206;,
 1049.64123;36.17410;-112.65752;,
 988.64015;36.17410;389.73419;,
 701.15377;36.17410;806.22911;,
 253.04051;36.17410;1041.41916;,
 -253.04051;36.17410;1041.41916;,
 -701.15353;36.17410;806.22911;,
 -988.64015;36.17410;389.73419;,
 -1049.64123;36.17410;-112.65752;,
 -870.18283;36.17410;-585.85206;,
 -491.37476;36.17410;-921.44747;,
 616.31334;0.00000;-1155.14338;,
 0.00000;0.00000;-1307.05061;,
 1091.43410;0.00000;-734.21974;,
 1316.52512;0.00000;-140.71051;,
 1240.01252;0.00000;489.41885;,
 879.42872;0.00000;1011.81466;,
 317.37884;0.00000;1306.80295;,
 -317.37884;0.00000;1306.80295;,
 -879.42872;0.00000;1011.81466;,
 -1240.01252;0.00000;489.41885;,
 -1316.52512;0.00000;-140.71051;,
 -1091.43410;0.00000;-734.21974;,
 -616.31187;0.00000;-1155.14338;;
 
 156;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,9,8;,
 3;0,10,9;,
 3;0,11,10;,
 3;0,12,11;,
 3;0,13,12;,
 3;0,2,13;,
 4;2,1,14,15;,
 4;1,3,16,14;,
 4;3,4,17,16;,
 4;4,5,18,17;,
 4;5,6,19,18;,
 4;6,7,20,19;,
 4;7,8,21,20;,
 4;8,9,22,21;,
 4;9,10,23,22;,
 4;10,11,24,23;,
 4;11,12,25,24;,
 4;12,13,26,25;,
 4;13,2,15,26;,
 4;15,14,27,28;,
 4;14,16,29,27;,
 4;16,17,30,29;,
 4;17,18,31,30;,
 4;18,19,32,31;,
 4;19,20,33,32;,
 4;20,21,34,33;,
 4;21,22,35,34;,
 4;22,23,36,35;,
 4;23,24,37,36;,
 4;24,25,38,37;,
 4;25,26,39,38;,
 4;26,15,28,39;,
 4;28,27,40,41;,
 4;27,29,42,40;,
 4;29,30,43,42;,
 4;30,31,44,43;,
 4;31,32,45,44;,
 4;32,33,46,45;,
 4;33,34,47,46;,
 4;34,35,48,47;,
 4;35,36,49,48;,
 4;36,37,50,49;,
 4;37,38,51,50;,
 4;38,39,52,51;,
 4;39,28,41,52;,
 4;41,40,53,54;,
 4;40,42,55,53;,
 4;42,43,56,55;,
 4;43,44,57,56;,
 4;44,45,58,57;,
 4;45,46,59,58;,
 4;46,47,60,59;,
 4;47,48,61,60;,
 4;48,49,62,61;,
 4;49,50,63,62;,
 4;50,51,64,63;,
 4;51,52,65,64;,
 4;52,41,54,65;,
 4;54,53,66,67;,
 4;53,55,68,66;,
 4;55,56,69,68;,
 4;56,57,70,69;,
 4;57,58,71,70;,
 4;58,59,72,71;,
 4;59,60,73,72;,
 4;60,61,74,73;,
 4;61,62,75,74;,
 4;62,63,76,75;,
 4;63,64,77,76;,
 4;64,65,78,77;,
 4;65,54,67,78;,
 4;67,66,79,80;,
 4;66,68,81,79;,
 4;68,69,82,81;,
 4;69,70,83,82;,
 4;70,71,84,83;,
 4;71,72,85,84;,
 4;72,73,86,85;,
 4;73,74,87,86;,
 4;74,75,88,87;,
 4;75,76,89,88;,
 4;76,77,90,89;,
 4;77,78,91,90;,
 4;78,67,80,91;,
 4;80,79,92,93;,
 4;79,81,94,92;,
 4;81,82,95,94;,
 4;82,83,96,95;,
 4;83,84,97,96;,
 4;84,85,98,97;,
 4;85,86,99,98;,
 4;86,87,100,99;,
 4;87,88,101,100;,
 4;88,89,102,101;,
 4;89,90,103,102;,
 4;90,91,104,103;,
 4;91,80,93,104;,
 4;93,92,105,106;,
 4;92,94,107,105;,
 4;94,95,108,107;,
 4;95,96,109,108;,
 4;96,97,110,109;,
 4;97,98,111,110;,
 4;98,99,112,111;,
 4;99,100,113,112;,
 4;100,101,114,113;,
 4;101,102,115,114;,
 4;102,103,116,115;,
 4;103,104,117,116;,
 4;104,93,106,117;,
 4;106,105,118,119;,
 4;105,107,120,118;,
 4;107,108,121,120;,
 4;108,109,122,121;,
 4;109,110,123,122;,
 4;110,111,124,123;,
 4;111,112,125,124;,
 4;112,113,126,125;,
 4;113,114,127,126;,
 4;114,115,128,127;,
 4;115,116,129,128;,
 4;116,117,130,129;,
 4;117,106,119,130;,
 4;119,118,131,132;,
 4;118,120,133,131;,
 4;120,121,134,133;,
 4;121,122,135,134;,
 4;122,123,136,135;,
 4;123,124,137,136;,
 4;124,125,138,137;,
 4;125,126,139,138;,
 4;126,127,140,139;,
 4;127,128,141,140;,
 4;128,129,142,141;,
 4;129,130,143,142;,
 4;130,119,132,143;,
 4;132,131,144,145;,
 4;131,133,146,144;,
 4;133,134,147,146;,
 4;134,135,148,147;,
 4;135,136,149,148;,
 4;136,137,150,149;,
 4;137,138,151,150;,
 4;138,139,152,151;,
 4;139,140,153,152;,
 4;140,141,154,153;,
 4;141,142,155,154;,
 4;142,143,156,155;,
 4;143,132,145,156;;
 
 MeshMaterialList {
  1;
  156;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/floor_01.jpg";
   }
  }
 }
 MeshNormals {
  157;
  -0.000000;0.999999;0.001441;,
  -0.000000;0.980548;-0.196279;,
  0.091281;0.980529;-0.173870;,
  0.161858;0.980475;-0.111669;,
  0.195597;0.980398;-0.023696;,
  0.184597;0.980314;0.070062;,
  0.131138;0.980242;0.148080;,
  0.047372;0.980201;0.192253;,
  -0.047372;0.980201;0.192253;,
  -0.131138;0.980242;0.148080;,
  -0.184596;0.980314;0.070063;,
  -0.195596;0.980398;-0.023696;,
  -0.161858;0.980475;-0.111670;,
  -0.091281;0.980529;-0.173870;,
  -0.000000;0.951141;-0.308755;,
  0.143423;0.951172;-0.273317;,
  0.253791;0.951255;-0.175227;,
  0.305794;0.951372;-0.037179;,
  0.287686;0.951495;0.109056;,
  0.203833;0.951598;0.230031;,
  0.073521;0.951655;0.298239;,
  -0.073521;0.951655;0.298239;,
  -0.203832;0.951598;0.230031;,
  -0.287686;0.951495;0.109056;,
  -0.305793;0.951372;-0.037179;,
  -0.253790;0.951255;-0.175228;,
  -0.143422;0.951172;-0.273317;,
  0.000000;0.930321;-0.366745;,
  0.170377;0.930355;-0.324671;,
  0.301541;0.930448;-0.208183;,
  0.363419;0.930578;-0.044171;,
  0.341990;0.930716;0.129655;,
  0.242362;0.930830;0.273525;,
  0.087429;0.930894;0.354672;,
  -0.087429;0.930894;0.354671;,
  -0.242361;0.930830;0.273525;,
  -0.341990;0.930716;0.129655;,
  -0.363419;0.930578;-0.044172;,
  -0.301541;0.930447;-0.208184;,
  -0.170377;0.930355;-0.324671;,
  0.000556;0.924837;-0.380364;,
  0.178167;0.924041;-0.338239;,
  0.315191;0.923745;-0.217601;,
  0.379915;0.923869;-0.046170;,
  0.357558;0.923999;0.135564;,
  0.253421;0.924108;0.286013;,
  0.091424;0.924169;0.370882;,
  -0.090630;0.924551;0.370124;,
  -0.251063;0.925313;0.284188;,
  -0.354087;0.925527;0.134247;,
  -0.376229;0.925398;-0.045722;,
  -0.312134;0.925276;-0.215490;,
  -0.176348;0.925190;-0.336042;,
  0.000714;0.885737;-0.464187;,
  0.216500;0.885547;-0.411015;,
  0.382028;0.885714;-0.263751;,
  0.460421;0.885935;-0.055961;,
  0.433271;0.886168;0.164263;,
  0.307050;0.886361;0.346532;,
  0.110765;0.886470;0.449335;,
  -0.110071;0.886460;0.449525;,
  -0.306215;0.886597;0.346666;,
  -0.432881;0.886386;0.164115;,
  -0.460008;0.886153;-0.055911;,
  -0.381686;0.885932;-0.263514;,
  -0.215662;0.885775;-0.410965;,
  0.013766;0.870207;-0.492494;,
  0.229527;0.863383;-0.449319;,
  0.410165;0.869531;-0.275101;,
  0.517239;0.854145;-0.053858;,
  0.495780;0.848020;0.187254;,
  0.349487;0.849827;0.394530;,
  0.126188;0.847730;0.515199;,
  -0.130594;0.841343;0.524488;,
  -0.369592;0.831513;0.414715;,
  -0.505790;0.837732;0.205868;,
  -0.501940;0.863591;-0.047619;,
  -0.392440;0.880035;-0.267451;,
  -0.209497;0.887674;-0.410055;,
  0.012320;0.871750;-0.489797;,
  0.218076;0.879455;-0.423086;,
  0.388308;0.884774;-0.257666;,
  0.466721;0.883268;-0.044820;,
  0.436777;0.884158;0.165805;,
  0.309966;0.884040;0.349850;,
  0.111936;0.884217;0.453466;,
  -0.111785;0.884081;0.453768;,
  -0.311893;0.882638;0.351672;,
  -0.437229;0.880698;0.182216;,
  -0.463286;0.885277;-0.040621;,
  -0.387043;0.882217;-0.268125;,
  -0.209727;0.875899;-0.434530;,
  -0.001302;0.864693;-0.502299;,
  0.222456;0.880157;-0.419328;,
  0.390958;0.880627;-0.267670;,
  0.445598;0.893758;-0.051365;,
  0.406699;0.900315;0.155013;,
  0.290214;0.899228;0.327361;,
  0.112922;0.913187;0.391585;,
  -0.065054;0.941547;0.330542;,
  -0.226535;0.946844;0.228406;,
  -0.379730;0.916556;0.125420;,
  -0.461184;0.885668;-0.053859;,
  -0.409886;0.865650;-0.287478;,
  -0.234872;0.849961;-0.471595;,
  0.000000;0.914669;-0.404204;,
  0.187535;0.914869;-0.357555;,
  0.331138;0.915421;-0.228805;,
  0.397790;0.916192;-0.048535;,
  0.373044;0.916999;0.141244;,
  0.263617;0.917661;0.297330;,
  0.112359;0.919132;0.377587;,
  -0.071687;0.930052;0.360367;,
  -0.258469;0.932360;0.252782;,
  -0.371835;0.921132;0.115124;,
  -0.397790;0.916192;-0.048535;,
  -0.331138;0.915421;-0.228804;,
  -0.187534;0.914869;-0.357554;,
  0.000000;0.952114;-0.305743;,
  0.141762;0.952267;-0.270355;,
  0.250037;0.952685;-0.172836;,
  0.299898;0.953267;-0.036660;,
  0.280782;0.953873;0.106244;,
  0.198151;0.954367;0.223426;,
  0.080610;0.946884;0.311309;,
  -0.083273;0.934363;0.346456;,
  -0.239068;0.935420;0.260452;,
  -0.299968;0.947750;0.108576;,
  -0.299899;0.953267;-0.036660;,
  -0.250038;0.952685;-0.172836;,
  -0.141762;0.952267;-0.270355;,
  0.000000;0.975944;-0.218021;,
  0.101064;0.976028;-0.192759;,
  0.178178;0.976257;-0.123182;,
  0.213580;0.976576;-0.026126;,
  0.199838;0.976908;0.075599;,
  0.140955;0.977178;0.158917;,
  0.050713;0.977329;0.205564;,
  -0.050713;0.977329;0.205564;,
  -0.140955;0.977178;0.158917;,
  -0.199838;0.976908;0.075599;,
  -0.213580;0.976576;-0.026126;,
  -0.178179;0.976257;-0.123183;,
  -0.101064;0.976028;-0.192759;,
  -0.000000;0.990776;-0.135507;,
  0.062803;0.990810;-0.119793;,
  0.110688;0.990904;-0.076533;,
  0.132621;0.991034;-0.016232;,
  0.124032;0.991169;0.046912;,
  0.087452;0.991278;0.098587;,
  0.031457;0.991339;0.127502;,
  -0.031457;0.991339;0.127502;,
  -0.087452;0.991278;0.098587;,
  -0.124032;0.991169;0.046912;,
  -0.132621;0.991034;-0.016232;,
  -0.110688;0.990904;-0.076533;,
  -0.062803;0.990810;-0.119793;;
  156;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,1,13;,
  4;1,2,15,14;,
  4;2,3,16,15;,
  4;3,4,17,16;,
  4;4,5,18,17;,
  4;5,6,19,18;,
  4;6,7,20,19;,
  4;7,8,21,20;,
  4;8,9,22,21;,
  4;9,10,23,22;,
  4;10,11,24,23;,
  4;11,12,25,24;,
  4;12,13,26,25;,
  4;13,1,14,26;,
  4;14,15,28,27;,
  4;15,16,29,28;,
  4;16,17,30,29;,
  4;17,18,31,30;,
  4;18,19,32,31;,
  4;19,20,33,32;,
  4;20,21,34,33;,
  4;21,22,35,34;,
  4;22,23,36,35;,
  4;23,24,37,36;,
  4;24,25,38,37;,
  4;25,26,39,38;,
  4;26,14,27,39;,
  4;27,28,41,40;,
  4;28,29,42,41;,
  4;29,30,43,42;,
  4;30,31,44,43;,
  4;31,32,45,44;,
  4;32,33,46,45;,
  4;33,34,47,46;,
  4;34,35,48,47;,
  4;35,36,49,48;,
  4;36,37,50,49;,
  4;37,38,51,50;,
  4;38,39,52,51;,
  4;39,27,40,52;,
  4;40,41,54,53;,
  4;41,42,55,54;,
  4;42,43,56,55;,
  4;43,44,57,56;,
  4;44,45,58,57;,
  4;45,46,59,58;,
  4;46,47,60,59;,
  4;47,48,61,60;,
  4;48,49,62,61;,
  4;49,50,63,62;,
  4;50,51,64,63;,
  4;51,52,65,64;,
  4;52,40,53,65;,
  4;53,54,67,66;,
  4;54,55,68,67;,
  4;55,56,69,68;,
  4;56,57,70,69;,
  4;57,58,71,70;,
  4;58,59,72,71;,
  4;59,60,73,72;,
  4;60,61,74,73;,
  4;61,62,75,74;,
  4;62,63,76,75;,
  4;63,64,77,76;,
  4;64,65,78,77;,
  4;65,53,66,78;,
  4;66,67,80,79;,
  4;67,68,81,80;,
  4;68,69,82,81;,
  4;69,70,83,82;,
  4;70,71,84,83;,
  4;71,72,85,84;,
  4;72,73,86,85;,
  4;73,74,87,86;,
  4;74,75,88,87;,
  4;75,76,89,88;,
  4;76,77,90,89;,
  4;77,78,91,90;,
  4;78,66,79,91;,
  4;79,80,93,92;,
  4;80,81,94,93;,
  4;81,82,95,94;,
  4;82,83,96,95;,
  4;83,84,97,96;,
  4;84,85,98,97;,
  4;85,86,99,98;,
  4;86,87,100,99;,
  4;87,88,101,100;,
  4;88,89,102,101;,
  4;89,90,103,102;,
  4;90,91,104,103;,
  4;91,79,92,104;,
  4;92,93,106,105;,
  4;93,94,107,106;,
  4;94,95,108,107;,
  4;95,96,109,108;,
  4;96,97,110,109;,
  4;97,98,111,110;,
  4;98,99,112,111;,
  4;99,100,113,112;,
  4;100,101,114,113;,
  4;101,102,115,114;,
  4;102,103,116,115;,
  4;103,104,117,116;,
  4;104,92,105,117;,
  4;105,106,119,118;,
  4;106,107,120,119;,
  4;107,108,121,120;,
  4;108,109,122,121;,
  4;109,110,123,122;,
  4;110,111,124,123;,
  4;111,112,125,124;,
  4;112,113,126,125;,
  4;113,114,127,126;,
  4;114,115,128,127;,
  4;115,116,129,128;,
  4;116,117,130,129;,
  4;117,105,118,130;,
  4;118,119,132,131;,
  4;119,120,133,132;,
  4;120,121,134,133;,
  4;121,122,135,134;,
  4;122,123,136,135;,
  4;123,124,137,136;,
  4;124,125,138,137;,
  4;125,126,139,138;,
  4;126,127,140,139;,
  4;127,128,141,140;,
  4;128,129,142,141;,
  4;129,130,143,142;,
  4;130,118,131,143;,
  4;131,132,145,144;,
  4;132,133,146,145;,
  4;133,134,147,146;,
  4;134,135,148,147;,
  4;135,136,149,148;,
  4;136,137,150,149;,
  4;137,138,151,150;,
  4;138,139,152,151;,
  4;139,140,153,152;,
  4;140,141,154,153;,
  4;141,142,155,154;,
  4;142,143,156,155;,
  4;143,131,144,156;;
 }
 MeshTextureCoords {
  157;
  0.577801;2.963204;,
  2.748845;6.982455;,
  0.577801;7.509444;,
  4.422523;5.522229;,
  5.215404;3.463283;,
  4.945888;1.277301;,
  3.675702;-0.534953;,
  1.695809;-1.558269;,
  -0.540207;-1.558269;,
  -2.520085;-0.534953;,
  -3.790283;1.277301;,
  -4.059812;3.463283;,
  -3.266903;5.522229;,
  -1.593229;6.982455;,
  5.339961;11.590354;,
  0.577801;12.746284;,
  9.011167;8.387346;,
  10.750387;3.871070;,
  10.159204;-0.923886;,
  7.373021;-4.899031;,
  3.030144;-7.143736;,
  -1.874527;-7.143736;,
  -6.217424;-4.899031;,
  -9.003595;-0.923886;,
  -9.594810;3.871070;,
  -7.855551;8.387346;,
  -4.184349;11.590354;,
  7.401784;15.131509;,
  0.577801;16.787905;,
  12.662474;10.541735;,
  15.154698;4.070081;,
  14.307530;-2.800896;,
  10.315094;-8.497137;,
  4.091904;-11.713696;,
  -2.936313;-11.713696;,
  -9.159470;-8.497137;,
  -13.151964;-2.800896;,
  -13.999116;4.070081;,
  -11.506886;10.541735;,
  -6.246170;15.131509;,
  9.368923;18.537304;,
  0.577801;20.671207;,
  16.146084;12.624458;,
  19.356766;4.287252;,
  18.265385;-4.564379;,
  13.122005;-11.902676;,
  5.104900;-16.046410;,
  -3.949304;-16.046410;,
  -11.966429;-11.902688;,
  -17.109770;-4.564379;,
  -18.201159;4.287252;,
  -14.990471;12.624458;,
  -8.213305;18.537317;,
  10.996449;21.308445;,
  0.577801;23.843332;,
  19.028353;14.300943;,
  22.833410;4.420223;,
  21.539997;-6.070187;,
  15.444381;-14.767019;,
  5.943042;-19.677994;,
  -4.787422;-19.677994;,
  -14.288780;-14.761131;,
  -20.384386;-6.064300;,
  -21.677790;4.426110;,
  -17.872746;14.306830;,
  -9.840860;21.314390;,
  12.617540;23.977938;,
  0.577801;26.900368;,
  21.899084;15.880118;,
  26.296272;4.461995;,
  24.801533;-7.660630;,
  17.757526;-17.710629;,
  6.777824;-23.385679;,
  -5.622208;-23.385679;,
  -16.601929;-17.710629;,
  -23.645962;-7.660640;,
  -25.140633;4.461995;,
  -20.743494;15.880118;,
  -11.461919;23.977938;,
  14.720082;25.802011;,
  -0.375739;29.466335;,
  24.731737;17.283054;,
  29.820038;4.065567;,
  28.140703;-9.554648;,
  20.226511;-20.846180;,
  7.890399;-27.222340;,
  -6.041529;-27.222340;,
  -18.377617;-20.846180;,
  -26.291862;-9.554648;,
  -28.842285;4.251989;,
  -23.328983;18.568394;,
  -11.691412;28.721773;,
  15.753016;29.443285;,
  0.500000;33.145687;,
  27.511824;19.184183;,
  33.082485;4.718666;,
  31.188923;-10.639407;,
  22.264858;-23.371674;,
  8.354767;-30.561392;,
  -7.354767;-30.561392;,
  -21.264858;-23.371674;,
  -30.188923;-10.639407;,
  -32.082485;4.718681;,
  -26.511824;19.184183;,
  -14.753014;29.443285;,
  17.656431;32.574512;,
  0.500000;36.739037;,
  30.882561;21.035204;,
  37.148350;4.764580;,
  35.018505;-12.509982;,
  24.980860;-26.831051;,
  9.334960;-34.917953;,
  -9.249476;-38.699978;,
  -26.280241;-28.206923;,
  -34.018505;-12.510005;,
  -36.148350;4.764580;,
  -29.882538;21.035225;,
  -16.656431;32.574570;,
  22.349731;40.673660;,
  0.500000;45.977325;,
  39.193962;25.977671;,
  47.173843;5.256054;,
  44.461273;-16.744087;,
  31.677818;-34.982918;,
  11.751826;-45.281952;,
  -10.751826;-45.281952;,
  -30.677818;-34.982918;,
  -43.461273;-16.744104;,
  -46.173843;5.256079;,
  -38.193962;25.977676;,
  -21.349728;40.673660;,
  25.068762;45.372097;,
  0.500000;51.335697;,
  44.009148;28.847260;,
  52.982059;5.546979;,
  49.932007;-19.190981;,
  35.557686;-39.699352;,
  13.152025;-51.280201;,
  -12.152025;-51.280201;,
  -34.557674;-39.699352;,
  -48.932007;-19.190981;,
  -51.982059;5.546979;,
  -43.009140;28.847260;,
  -24.068737;45.372105;,
  31.315666;56.565304;,
  0.500000;64.045273;,
  55.071701;35.838863;,
  66.326256;6.614241;,
  62.500622;-24.413570;,
  44.471436;-50.136539;,
  16.368942;-64.661880;,
  -15.368941;-64.661880;,
  -43.471436;-50.136539;,
  -61.500622;-24.413570;,
  -65.326256;6.614241;,
  -54.071701;35.838863;,
  -30.315592;56.565304;;
 }
}
