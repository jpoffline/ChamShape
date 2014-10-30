function tri(varargin)

    l1=str2num(char(varargin(1)));
    l2=str2num(char(varargin(2)));
    l3=sqrt(l1*l1-(l2/2)*(l2/2));
    

    A = [0 l3/2];
    B = [l2/2  -l3/2];
    C = [-l2/2 -l3/2];
    
    x = [A(1) B(1) C(1)];
    y = [A(2) B(2) C(2)];
    
    line1_x=[A(1) B(1)];
    line1_y=[A(2) B(2)];
    line2_x=[B(1) C(1)];
    line2_y=[B(2) C(2)];
    line3_x=[C(1) A(1)];
    line3_y=[C(2) A(2)];
    
    plot(x,y,'*');
    hold on;
    plot(line1_x,line1_y,'k');
    plot(line2_x,line2_y,'k');
    plot(line3_x,line3_y,'k');
    xlim([-1 1]);
    ylim([-1 1]);
    
    