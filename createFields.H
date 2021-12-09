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

dimensionedScalar Gammac
(
    transportProperties.lookup("Gammac")
);

Info<< "Reading field C\n" << endl;
volScalarField C
(
    IOobject
    (
        "C",
	runTime.timeName(),
	mesh,
	IOobject::MUST_READ,
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

#include "createMRF.H"
#include "createFvModels.H"
#include "createFvConstraints.H"
