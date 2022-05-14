dimensionedScalar Ksist = C1/(C1+C2);

Info<<"Reaction progress equation establishing"<<endl;

volScalarField reactionCorrectionCoe = (1-sqr(KsiVar)/(Ksi*(1-Ksi)));

volScalarField ysource = Ksist*k*C2*reactionCorrectionCoe*((1-Ksi)/(1-Ksist)-y)*(Ksi/Ksist-y);

fvScalarMatrix yEqn(
    fvm::ddt(y)
    ==
    fvm::Su(ysource,y)
);

Info<<"Reaction progress equation solving"<<endl;

yEqn.solve();

