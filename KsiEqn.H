
Info<< "Solving Mixture Fraction Eqns" << endl;

volScalarField GammaT = (mfCmu/mfSct)*sqr(turbulence->k())/(turbulence->epsilon());
volScalarField Gammas = (mfCphi/2)*(turbulence->epsilon()/turbulence->k());

fvScalarMatrix Ksieqn(
    fvm::ddt(Ksi)
    +fvm::div(phi,Ksi)
    -fvm::laplacian(GammaT,Ksi)
);

volScalarField Ksigrad = magSqr(fvc::grad(Ksi));

fvScalarMatrix KsiVareqn(
    fvm::ddt(KsiVar)
    +fvm::div(phi,KsiVar)
    ==
    fvm::laplacian(GammaT,KsiVar)
    +fvm::Su(2*GammaT*Ksigrad, KsiVar)
    -fvm::SuSp(2*Gammas*KsiVar, KsiVar)
);

Info << "Solving Mixture Fraction Transport Model" << endl;

Ksieqn.solve();
KsiVareqn.solve();



