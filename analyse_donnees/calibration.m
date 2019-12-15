clear all;
close all;
%calcul des valeurs moyennes selon différents sénario

%% calme
bender= [1134;1339;1309;1169;1101;1075];
%bender= [1256;1289;1239;1283;1261;1216];
%bender=[571;1263;1274;600;1273;1272];
%bender=[669;1287;1297;605;1261;1267];
%bender=[1354;1512;92;1256;1307;620];
bender = 3*bender/1000;
norme = [121;119;108;112;109;108];
%norme = [99;102;141;105;105;11];
%norme = [104;97;97;141;98;97];
%norme=[108;96;97;72;96;96];
%norme=[96;97;93;97;97;132];
norme = norme/1000;
sumb = 0;
sumn = 0;
calmebender =0;
calmemma =0;
for i=1:6
   %bender(i)
  sumb = sumb + bender(i);
  sumn = sumn + norme(i);
end
calmebender = sumb/6
calmemma = sumn/6


%tracé des conditions calme
time = [10;20;30;40;50;60];
%figure(1)
figure ('Name','calme')
t.Padding = 'none';
t.TileSpacing = 'none';
subplot(2,1,1);
plot(time(1 : end),bender);
xlabel({'temps','(en s)'});
ylabel({'tension','(en mV)'});
str = ['moyenne =  ',num2str(calmebender)];
text(40,3.6,str,'Color','r')
title('bender');

subplot(2,1,2);
plot(time(1 : end),norme);
hold on;
seuil_1 = [0.1,0.1,0.1,0.1,0.1,0.1];
plot(time(1 : end),seuil_1,'Color','g');
text(20,0.105,'seuil_1','Color','g');
seuil_2 = [0.2,0.2,0.2,0.2,0.2,0.2];
plot(time(1 : end),seuil_2,'Color','m');
text(40,0.18,'seuil_2','Color','m');
hold off;
xlabel({'temps','(en s)'});
ylabel({'accéleration','(en M/s²)'});
title('mma');
str = ['moyenne =  ',num2str(calmemma)];
text(30,0.115,str,'Color','r')



%% agitation moyenne
bender= [497;1294;1234;1303;1314;1246];
%bender=[1393;1398;1387;1369;1386;1331];
%bender=[1273;1287;1265;1296;1294;1276];
bender = 3*bender/1000;
norme = [377;137;185;227;255;244];
%norme=[130;172;157;177;160;186];
%norme=[477;132;241;196;169;149];
norme = norme/1000;
sumb = 0;
sumn = 0;
for i=1:6
   %bender(i)
  sumb = sumb + bender(i);
  sumn = sumn + norme(i);
end
moyenbender = sumb/6
moyenmma = sumn/6


%tracé des conditions moyennes
time = [10;20;30;40;50;60];
figure ('Name','moyen')
t.Padding = 'none';
t.TileSpacing = 'none';
subplot(2,1,1);
plot(time(1 : end),bender);
xlabel({'temps','(en s)'});
ylabel({'tension','(en mV)'});
str = ['moyenne =  ',num2str(moyenbender)];
text(20,3,str,'Color','r')
title('bender');

subplot(2,1,2);
plot(time(1 : end),norme);
hold on
seuil_1 = [0.1,0.1,0.1,0.1,0.1,0.1];
plot(time(1 : end),seuil_1,'Color','g');
text(30,0.15,'seuil_1','Color','g');
seuil_2 = [0.2,0.2,0.2,0.2,0.2,0.2];
plot(time(1 : end),seuil_2,'Color','m');
text(40,0.25,'seuil_2','Color','m');
xlabel({'temps','(en s)'});
ylabel({'accéleration','(en M/s²)'});
title('mma');
str = ['moyenne =  ',num2str(moyenmma)];
text(20,0.3,str,'Color','r')


%% agitation forte
%bender= [1134;1339;1309;1169;1101;1075];
bender = 3*bender/1000;
%norme = [94;93;99;94;94;94];
%norme = [121;119;108;112;109;108];
norme = norme/1000;
sumb = 0;
sumn = 0;
fortbender =0;
fortmma =0;
for i=1:6
   %bender(i)
  sumb = sumb + bender(i);
  sumn = sumn + norme(i);
end
fortbender = sumb/6
fortmma = sumn/6


%tracé des conditions agitées
time = [10;20;30;40;50;60];
%figure(2)
figure ('Name','agitées')
t.Padding = 'none';
t.TileSpacing = 'none';
subplot(2,1,1);
plot(time(1 : end),bender);
xlabel({'temps','(en s)'});
ylabel({'tension','(en mV)'});
str = ['moyenne =  ',num2str(fortbender)];
text(40,3.6,str,'Color','r')
title('bender');

subplot(2,1,2);
plot(time(1 : end),norme);
xlabel({'temps','(en s)'});
ylabel({'accéleration','(en M/s²)'});
title('mma');
str = ['moyenne =  ',num2str(fortmma)];
text(30,0.115,str,'Color','r')



