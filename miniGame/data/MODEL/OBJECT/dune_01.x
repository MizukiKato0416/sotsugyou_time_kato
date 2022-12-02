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
 74;
 -449.12945;394.59947;-298.11853;,
 -184.03396;461.29234;-298.11853;,
 -115.41205;396.79649;-658.02315;,
 -737.23048;262.85948;-533.87921;,
 81.92138;503.98834;-298.11853;,
 104.07427;396.79649;-658.02315;,
 301.40718;524.30553;-298.11853;,
 323.56016;396.79649;-658.02315;,
 581.55538;543.21471;-298.11853;,
 701.20265;396.79649;-658.02315;,
 768.34982;456.52423;-408.00482;,
 918.90617;396.79649;-399.28687;,
 -146.74856;293.47496;-921.68654;,
 -965.98468;170.57427;-747.04127;,
 98.19186;293.47496;-921.68654;,
 343.13216;293.47496;-921.68654;,
 764.57086;293.47496;-921.68654;,
 1104.78703;281.30191;-677.65724;,
 -708.20314;153.54917;-1142.93722;,
 -1139.27785;100.97427;-877.46886;,
 98.19186;153.54917;-1142.93722;,
 343.13216;153.54917;-1142.93722;,
 764.57086;153.54917;-1143.54552;,
 1253.02951;154.55171;-946.93693;,
 -790.39879;5.95212;-1365.29133;,
 -1188.19650;0.00000;-1126.55265;,
 81.44971;2.27559;-1482.41789;,
 417.04229;0.11279;-1414.58381;,
 1151.87092;4.32205;-1514.22307;,
 1348.97326;2.97393;-1282.60090;,
 719.75792;487.28951;285.17989;,
 555.11563;522.93902;285.17989;,
 543.04552;396.79649;588.03634;,
 918.90617;396.79649;381.23067;,
 274.96849;504.02984;285.17989;,
 337.69090;394.49708;607.59615;,
 55.48248;483.71246;285.17989;,
 104.07427;396.79649;583.42335;,
 -210.47320;441.01671;285.17989;,
 -115.41205;369.91719;529.20587;,
 -475.56876;374.32359;285.17989;,
 -737.23048;262.85948;477.66021;,
 543.04552;279.86866;742.06959;,
 1141.23888;293.47496;458.56441;,
 323.56016;279.86866;725.10577;,
 104.07427;279.86866;697.57833;,
 -90.25728;266.81910;698.45621;,
 -940.83048;157.52447;574.61070;,
 648.92755;148.17974;1025.29943;,
 1254.68273;153.54917;586.79361;,
 343.13216;153.54917;940.19718;,
 98.19186;153.54917;909.16954;,
 -668.51515;131.00747;886.02394;,
 -993.09289;99.46270;866.45431;,
 735.27394;3.27144;1307.20686;,
 1348.97326;13.62314;819.49396;,
 343.13216;2.93457;1429.54758;,
 -29.56606;2.18569;1514.22307;,
 -754.28951;13.62314;1394.05393;,
 -1141.21418;6.59106;984.75158;,
 1073.58361;413.40049;-148.09054;,
 889.08410;510.21148;-155.33721;,
 1264.48264;297.79664;-120.84466;,
 1424.20031;175.54961;-107.96128;,
 1617.21165;2.72124;-112.37688;,
 -702.57750;315.40684;-98.85660;,
 -478.45196;434.10513;-98.85660;,
 -1029.16535;203.35557;-116.77061;,
 -1203.42336;133.35445;-112.61633;,
 -1617.21165;17.61143;-465.36519;,
 -198.74846;498.27945;-98.85660;,
 79.88743;516.15377;-98.85660;,
 307.77127;557.94605;-98.85660;,
 616.40641;575.29058;-98.85660;;
 
 66;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;3,2,12,13;,
 4;2,5,14,12;,
 4;5,7,15,14;,
 4;7,9,16,15;,
 4;9,11,17,16;,
 4;13,12,18,19;,
 4;12,14,20,18;,
 4;14,15,21,20;,
 4;15,16,22,21;,
 4;16,17,23,22;,
 4;19,18,24,25;,
 4;18,20,26,24;,
 4;20,21,27,26;,
 4;21,22,28,27;,
 4;22,23,29,28;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;33,32,42,43;,
 4;32,35,44,42;,
 4;35,37,45,44;,
 4;37,39,46,45;,
 4;39,41,47,46;,
 4;43,42,48,49;,
 4;42,44,50,48;,
 4;44,45,51,50;,
 4;45,46,52,51;,
 4;46,47,53,52;,
 4;49,48,54,55;,
 4;48,50,56,54;,
 4;50,51,57,56;,
 4;51,52,58,57;,
 4;52,53,59,58;,
 4;60,61,30,33;,
 4;61,60,11,10;,
 4;62,60,33,43;,
 4;60,62,17,11;,
 4;63,62,43,49;,
 4;62,63,23,17;,
 4;64,63,49,55;,
 4;63,64,29,23;,
 4;65,66,0,3;,
 4;66,65,41,40;,
 4;67,65,3,13;,
 4;65,67,47,41;,
 4;68,67,13,19;,
 4;67,68,53,47;,
 4;69,68,19,25;,
 4;68,69,59,53;,
 4;70,66,40,38;,
 4;66,70,1,0;,
 4;71,70,38,36;,
 4;70,71,4,1;,
 4;72,71,36,34;,
 4;71,72,6,4;,
 4;73,72,34,31;,
 4;72,73,8,6;,
 4;61,73,31,30;,
 4;73,61,10,8;;
 
 MeshMaterialList {
  1;
  66;
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
  74;
  -0.294286;0.935220;-0.196873;,
  -0.165761;0.965689;-0.199920;,
  -0.092473;0.975664;-0.198818;,
  -0.068490;0.969463;-0.235478;,
  0.111106;0.956371;-0.270205;,
  -0.298908;0.936255;-0.184609;,
  -0.137530;0.951092;-0.276603;,
  -0.030577;0.946142;-0.322305;,
  -0.018983;0.936612;-0.349854;,
  0.135378;0.936231;-0.324261;,
  -0.275664;0.949084;-0.152478;,
  -0.110056;0.933328;-0.341740;,
  0.000000;0.892156;-0.451728;,
  -0.000097;0.892226;-0.451590;,
  0.122317;0.909183;-0.398026;,
  -0.292922;0.934297;-0.203187;,
  -0.136248;0.907047;-0.398374;,
  0.004021;0.868483;-0.495702;,
  0.004466;0.870123;-0.492814;,
  0.094973;0.900136;-0.425129;,
  -0.303736;0.911236;-0.278196;,
  -0.165353;0.886968;-0.431214;,
  0.008038;0.890031;-0.455829;,
  0.009118;0.892890;-0.450183;,
  0.074066;0.925757;-0.370795;,
  0.313375;0.901234;-0.299289;,
  0.343506;0.897429;-0.276814;,
  0.364287;0.893632;-0.262137;,
  0.417338;0.871611;-0.257143;,
  0.432256;0.874542;-0.219845;,
  0.281011;0.929102;0.240423;,
  0.091439;0.960512;0.262784;,
  -0.068450;0.971683;0.226155;,
  -0.118773;0.970364;0.210443;,
  -0.180731;0.957499;0.224792;,
  0.333834;0.889718;0.311379;,
  0.114970;0.862628;0.492601;,
  -0.039399;0.855494;0.516311;,
  -0.112906;0.858232;0.500689;,
  -0.177110;0.873208;0.454026;,
  0.413869;0.849364;0.327555;,
  0.115188;0.835017;0.538032;,
  -0.055036;0.805291;0.590320;,
  -0.082452;0.802800;0.590520;,
  -0.127714;0.871878;0.472777;,
  0.472146;0.827917;0.302706;,
  0.127849;0.896129;0.424979;,
  -0.024393;0.912226;0.408961;,
  -0.033221;0.922930;0.383531;,
  -0.107792;0.948013;0.299421;,
  0.481125;0.826531;0.292173;,
  0.159218;0.912354;0.377173;,
  0.021174;0.948065;0.317371;,
  -0.009661;0.967836;0.251397;,
  -0.124381;0.962354;0.241670;,
  -0.284787;0.939316;0.191265;,
  -0.299299;0.916352;0.265932;,
  -0.271652;0.932906;0.236413;,
  -0.286084;0.942364;0.173511;,
  -0.316382;0.929141;0.191310;,
  -0.324371;0.945417;-0.031133;,
  -0.172677;0.984784;-0.019575;,
  -0.123887;0.992278;-0.006066;,
  -0.099141;0.995029;-0.009373;,
  0.084532;0.995939;-0.030966;,
  -0.377800;0.925788;-0.013575;,
  -0.354153;0.935134;0.010021;,
  -0.364656;0.931140;-0.002175;,
  -0.364518;0.930939;-0.021913;,
  0.323596;0.943645;-0.069425;,
  0.419795;0.905378;-0.063744;,
  0.517486;0.855480;-0.019034;,
  0.634809;0.772633;0.007473;,
  0.664056;0.747523;0.015418;;
  66;
  4;0,1,6,5;,
  4;1,2,7,6;,
  4;2,3,8,7;,
  4;3,4,9,8;,
  4;4,25,26,9;,
  4;5,6,11,10;,
  4;6,7,12,11;,
  4;7,8,13,12;,
  4;8,9,14,13;,
  4;9,26,27,14;,
  4;10,11,16,15;,
  4;11,12,17,16;,
  4;12,13,18,17;,
  4;13,14,19,18;,
  4;14,27,28,19;,
  4;15,16,21,20;,
  4;16,17,22,21;,
  4;17,18,23,22;,
  4;18,19,24,23;,
  4;19,28,29,24;,
  4;30,31,36,35;,
  4;31,32,37,36;,
  4;32,33,38,37;,
  4;33,34,39,38;,
  4;34,55,56,39;,
  4;35,36,41,40;,
  4;36,37,42,41;,
  4;37,38,43,42;,
  4;38,39,44,43;,
  4;39,56,57,44;,
  4;40,41,46,45;,
  4;41,42,47,46;,
  4;42,43,48,47;,
  4;43,44,49,48;,
  4;44,57,58,49;,
  4;45,46,51,50;,
  4;46,47,52,51;,
  4;47,48,53,52;,
  4;48,49,54,53;,
  4;49,58,59,54;,
  4;70,69,30,35;,
  4;69,70,26,25;,
  4;71,70,35,40;,
  4;70,71,27,26;,
  4;72,71,40,45;,
  4;71,72,28,27;,
  4;73,72,45,50;,
  4;72,73,29,28;,
  4;65,60,0,5;,
  4;60,65,56,55;,
  4;66,65,5,10;,
  4;65,66,57,56;,
  4;67,66,10,15;,
  4;66,67,58,57;,
  4;68,67,15,20;,
  4;67,68,59,58;,
  4;61,60,55,34;,
  4;60,61,1,0;,
  4;62,61,34,33;,
  4;61,62,2,1;,
  4;63,62,33,32;,
  4;62,63,3,2;,
  4;64,63,32,31;,
  4;63,64,4,3;,
  4;69,64,31,30;,
  4;64,69,25,4;;
 }
 MeshTextureCoords {
  74;
  -21.956472;17.791147;,
  -8.701697;18.370201;,
  -5.270602;35.532063;,
  -36.361523;28.256271;,
  4.596069;18.740906;,
  5.703713;35.532063;,
  15.570358;18.917309;,
  16.678007;35.532063;,
  29.577768;19.081486;,
  35.560131;35.532063;,
  38.917488;23.739645;,
  46.445305;22.791790;,
  -6.837428;47.617870;,
  -47.799232;37.951195;,
  5.409593;47.617870;,
  17.656607;47.617870;,
  38.728542;47.617870;,
  55.739349;35.496082;,
  -34.910156;57.297447;,
  -56.463890;43.769203;,
  5.409593;57.297447;,
  17.656607;57.297447;,
  38.728542;57.327396;,
  63.151474;47.655022;,
  -39.019939;66.964752;,
  -58.909824;55.157486;,
  4.572485;72.700188;,
  21.352114;69.341232;,
  58.093544;74.284050;,
  67.948662;62.867184;,
  36.487896;-10.125918;,
  28.255781;-9.816395;,
  27.652275;-25.824383;,
  46.445305;-15.641193;,
  14.248424;-9.980572;,
  17.384544;-26.807482;,
  3.274124;-10.156976;,
  5.703713;-25.597239;,
  -10.023660;-10.527678;,
  -5.270602;-23.160925;,
  -23.278437;-11.106735;,
  -36.361523;-21.552317;,
  27.652275;-34.424255;,
  57.561943;-20.346216;,
  16.678007;-33.588951;,
  5.703713;-32.233490;,
  -4.012864;-32.390018;,
  -46.541523;-27.240759;,
  32.946377;-49.513977;,
  63.234135;-27.875164;,
  17.656607;-45.276894;,
  5.409593;-43.749081;,
  -32.925755;-42.805096;,
  -49.154644;-42.115364;,
  37.263695;-64.653358;,
  67.948662;-40.548313;,
  17.656607;-70.680389;,
  -0.978303;-74.856346;,
  -37.214474;-68.839867;,
  -56.560707;-48.746719;,
  54.179180;10.566949;,
  44.954205;11.764331;,
  63.724129;8.221631;,
  71.710014;6.525850;,
  81.360580;5.242709;,
  -34.628872;7.291830;,
  -23.422598;8.322416;,
  -50.958267;7.201047;,
  -59.671165;6.388710;,
  -80.360580;22.753271;,
  -9.437423;8.879604;,
  4.494371;9.034797;,
  15.888563;9.397655;,
  31.320318;9.548247;;
 }
}
