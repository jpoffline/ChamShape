function phi = phi_Guess(phi_cen, phi_inf, R, s)
    phi(x) = phi_inf * ( 1.0 + 0.5 * ( phi_cen / phi_inf - 1.0 ) * ( 1.0 - tanh( ( x - R ) / s ) ) );
