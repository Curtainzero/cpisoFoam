Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);


Info<< "Reading field Mixture fraction Kesi\n" << endl;
volScalarField Ksi
(
    IOobject
    (
        "Ksi",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
    IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Creating field for Mixture fraction variance" << endl;
volScalarField KsiVar
(
    IOobject
    (
    "KsiVar",
	runTime.timeName(),
	mesh,
	IOobject::NO_READ,
    IOobject::AUTO_WRITE
    ),
    mesh
);


#include "createPhi.H"


pressureReference pressureReference(p, piso.dict());

mesh.setFluxRequired(p.name());


singlePhaseTransportModel laminarTransport(U, phi);

autoPtr<incompressible::momentumTransportModel> turbulence
(
    incompressible::momentumTransportModel::New(U, phi, laminarTransport)
);


Info << "Creating Constants for Mixture tansport model" << endl;

dimensionedScalar mfSct = 0.7;
dimensionedScalar mfCmu = 0.09;
dimensionedScalar mfCphi = 2;

#include "createMRF.H"
#include "createFvModels.H"
#include "createFvConstraints.H"
