fvScalarMatrix Ceqn
(
fvm::ddt(C)
+fvm::div(phi,C)
-fvm::laplacian(Gammac,C)
);




Ceqn.solve();