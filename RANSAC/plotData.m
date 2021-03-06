clear all;
close all;
clc;

for i = 1:4  
  switch (i)
    case 1
      aC = -1;
      lC = 0;
    case 2
      aC = -3;
      lC = 0;
    case 3
      aC = -5;
      lC = 0;
    case 4
      aC = -20;
      lC = 0;
  endswitch
  
  system(cstrcat("E:/Users/favero.santos/source/repos/RANSAC/Debug/RANSAC.exe", " ", int2str(aC), " ", int2str(lC)));

  myData = load("data.txt");
  x = myData(1:end-2,1);
  y = myData(1:end-2,2);

  figure();
  scatter(x,y, "*");

  X = [-100:1:100];
  Y = [-100:1:100];

  angularCoefficient = myData(end-1,1);
  linearCoefficient = myData(end-1,2);

  for i = 1:size(X)(2)
    Y(i) = angularCoefficient*X(i) + linearCoefficient;
  endfor

  hold on;
  plot(X,Y, "linewidth", 2);
  legend("Coefs M0", "Coefs M1");
  
  angularCoefficient = myData(end,1);
  linearCoefficient = myData(end,2);

  for i = 1:size(X)(2)
    Y(i) = angularCoefficient*X(i) + linearCoefficient;
  endfor

  hold on;
  plot(X,Y, "linewidth", 2);
  legend("Cloud Data", "Coefs M0", "Coefs M1");
endfor