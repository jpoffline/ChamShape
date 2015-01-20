
function plotsol

    close all;
    npx = 3;
    npy = 2;
    syms f(x) y(x) real;
    
    R = 1;
    s = 0.1;
    Lambda5_start = 0.000005;
    M = 0.1;
    nt = 10;
    Lambda5 = Lambda5_start;
    
    for tt = 1:nt

        Lambda5 = Lambda5 + 0.0005;
        fprintf('Lambda5 = %f\n', Lambda5);
        rho_cen = 1000.0;
        rho_inf = 1;

        phi_cen = sqrt( M * Lambda5 / rho_cen );
        phi_inf = sqrt( M * Lambda5 / rho_inf );

        % Functional form of the ansatz for phi(r)
        phi(x) = phi_inf * ( 1.0 + 0.5 * ( phi_cen / phi_inf - 1.0 ) * ( 1.0 - tanh( ( x - R ) / s ) ) );

        % Compute phi'
        dfdx(x) = diff( phi(x) );
        % Compute nabla^2phi
        lap(x) = 1.0 / x * diff( x * dfdx(x) );
        % Compute F
        F(x) = 1 / M * diff( phi(x) );
        % Compute 1 / phi^2
        ups(x) = 1.0 / phi(x) / phi(x);
        % Compute the relevant \rho from the equation of motion
        rho(x) = lap(x) + Lambda5 / phi(x) / phi(x);

        drhodx(x) = diff(rho(x));
        r = [ 0.01 : min( 0.1 , s / 5 ) : 2 * R ];

        rr=size(r);
        nrs = rr(2);
        for i=1:nrs
            neg_found = false;
            if rho( r(i) ) < 0
                fprintf('NOTE: rho goes negative\n')
                neg_found = true;
                break;
            end;
        end;
        if not(neg_found)
            break;
        end;
    end;
        
    fprintf('phi_cen = %f, phi_bg = %f\n',phi_cen, phi_inf);
    fprintf('rho_cen = %f, rho_bg = %f\n',eval(rho(min(r))),eval(rho(max(r))));
    subplot(npy,npx,1);
    plot(r,phi(r));
    xlabel('r');
    ylabel('$\phi(r)$', 'interpreter','latex');
    subplot(npy,npx,2);
    plot(r,rho(r));
    xlabel('r');
    ylabel('$\rho(r)$', 'interpreter','latex');
    subplot(npy,npx,3);
    plot(r,F(r));
    xlabel('r');
    ylabel('$F(r)$', 'interpreter','latex');
    subplot(npy,npx,4);
    plot(r,lap(r));
    xlabel('r');
    ylabel('$\nabla^2\phi$', 'interpreter','latex');
    subplot(npy,npx,5);
    plot(r, ups(r));
    xlabel('r');
    ylabel('$1/\phi^2$', 'interpreter','latex');
    subplot(npy,npx,6);
    plot(r, drhodx(r));
    xlabel('r');
    ylabel('$|d\rho/dr|$', 'interpreter','latex');
    