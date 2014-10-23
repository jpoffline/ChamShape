function plotb(varargin)

    fprintf('Plotting the surface and x- and y-axes plots');

    % pull off of input the "name"... folder name for run
    name = char(varargin(1));
    % which file do we want? usually "final"
    which = char(varargin(2));
    % what type of thing to plot? force or cham
    whichID = char(varargin(3));
    
    plotxy(name,which.whichID);
    makesurf(name,which,whichID);
    
    fprintf('Done');