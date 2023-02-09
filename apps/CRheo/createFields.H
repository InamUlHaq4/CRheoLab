
    volScalarField p 
    (
        IOObject
        (
            "p",
            time.timeName(),
            mesh,
            IOObject::MUST_READ,
            IOObject::MUST_WRITE
        )
    );

    volVectorField U
    (
        IOObject
        (
            "U",
            time.timeName(),
            mesh,
            IOObject::MUST_READ,
            IOObject::NO_WRITE
        )
    );

    Dictionary myDict
    (
        IOObject
        (
            "transportProperties",
            time.constant(),
            mesh,
            IOObject::MUST_READ,
            IOObject::NO_WRITE
        )
    );

   fvSolution fvSolutionDict
    (
        IOObject
        (
            "fvSolution",
            time.system(),
            mesh,
            IOObject::MUST_READ,
            IOObject::NO_WRITE
        )
    );

    fvSolutionDict.solverDict("sigmaHyd", fvSolutionDict);
    fvSolutionDict.checkRelaxationFactors("relaxationFactors");

    scalar DT = myDict.lookup<scalar>("DT");
    scalar DT2 = myDict.lookup<scalar>("DT_2");


