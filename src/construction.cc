#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    fMessengar = new G4GenericMessenger(this, "/detector/", "Detector Construction");
    fMessengar->DeclareProperty("SDD", SDD, "Source to detector distance ");
    SDD = 20;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    /*______________________________________________________________________________________________________________*/

    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");

    // Al housing of the detector
    G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
    G4Element* Na = nist->FindOrBuildElement("Na");
    G4Element* I = nist->FindOrBuildElement("I");

    // Defining source container 
    G4Element* C = new G4Element("Carbon", "C", 6, 12.011 * g / mole);  // Carbon
    G4Element* H = new G4Element("Hydrogen", "H", 1, 1.008 * g / mole);  // Hydrogen

    // Define the elements involved in MgO
    G4Element* magnesium = new G4Element("Magnesium", "Mg", 12, 24.305 * g / mole);
    G4Element* oxygen = new G4Element("Oxygen", "O", 8, 15.999 * g / mole);

    // Define the material (MgO)
    G4Material* MgO = new G4Material("Magnesium Oxide", 3.58 * g / cm3, 2);
    MgO->AddElement(magnesium, 1);
    MgO->AddElement(oxygen, 1);

    // Define the  Acrylic Material
    G4Material *PMMA = new G4Material("PMMA",1.18* g / cm3,3);
    PMMA->AddElement(H,8);
    PMMA->AddElement(C,5);
    PMMA->AddElement(oxygen,2);

    // Entire Simulation Environment
    auto solidWorld = new G4Box("World", 2 * m, 2 * m, 2 * m);
    auto logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    auto physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    // Define NaI(Tl) Material
    G4Material* NaI_Tl = new G4Material("NaI_Tl", 3.67 * g / cm3, 2);
    NaI_Tl->AddElement(Na, 1);
    NaI_Tl->AddElement(I, 1);

    /*__________________________________________________________________________________________________________________*/

    // Define Material Properties
    G4double energy[1] = {661.7 * keV};
    // Refractive Index of NaI
    G4double rindexNaI[1] = {1.786};
    G4double fraction[1] = {1.0};

    // Defining Material properties of NaI
    G4MaterialPropertiesTable* mptNaI = new G4MaterialPropertiesTable();
    mptNaI->AddProperty("RINDEX", energy, rindexNaI, 1);
    mptNaI->AddProperty("FASTCOMPONENT", energy, fraction, 1, true);
    mptNaI->AddConstProperty("SCINTILLATIONYIELD", 38. / keV);
    mptNaI->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptNaI->AddConstProperty("FASTTIMECONSTANT", 250. * ns, true);
    mptNaI->AddConstProperty("YIELDRATIO", 1.0, true);
    NaI_Tl->SetMaterialPropertiesTable(mptNaI);

    G4double innerRadius = 51.17 * mm;         // Inner radius
    G4double outerRadius = 58.88 * mm;         // Outer radius 
    G4double halfThickness = 50.80 * mm;       // HalfThickness of the disc


    /*__________________________________________________________________________________________________________________*/

    // Defining Detector Geometry

    //  Crystal Material
    G4Tubs* NaI_Tube = new G4Tubs("NaI_Tube", 0, 25.4 * mm, halfThickness/2, 0, 2 * CLHEP::pi);
    NaI_Logical = new G4LogicalVolume(NaI_Tube, NaI_Tl, "NaI_Logical");
    fScoringVolume = NaI_Logical;
    G4VPhysicalVolume* physVolume = new G4PVPlacement(0, G4ThreeVector(0, 0., (SDD+2.54) * cm), NaI_Logical, "NaI_Logical", logicWorld, false, 0, true);

    // Defining MgO reflector surface
    G4Tubs* MgO_Solid = new G4Tubs("MgO_Solid", innerRadius / 2 - 0.185 * mm, outerRadius / 2 - 3.855 * mm, halfThickness/2, 0, 2 * CLHEP::pi);
    G4LogicalVolume* MgO_Logical = new G4LogicalVolume(MgO_Solid, MgO, "MgO_Logical");
    G4VPhysicalVolume* MgO_Phys = new G4PVPlacement(0, G4ThreeVector(0, 0., (SDD+2.54) * cm), MgO_Logical, "MgO_Logical", logicWorld, false, 0, true);

    // Defining Al Material
    G4Tubs* Al_Solid = new G4Tubs("Al_Solid", 25.585 * mm, 26.085 * mm, halfThickness/2, 0, 2 * CLHEP::pi);
    G4LogicalVolume* Al_Logical = new G4LogicalVolume(Al_Solid, Al, "Al_Logical");
    G4VPhysicalVolume* Al_Phys = new G4PVPlacement(0, G4ThreeVector(0, 0., (SDD+2.54) * cm), Al_Logical, "Al_Logical", logicWorld, false, 0, true);

    // Defining End Cap for detector 
    G4Tubs* EndCap = new G4Tubs(
        "EndCap",               // Name of Solid
        0,                      // Inner Radius
        26.085 * mm,            // Outer Radius
        0.5 * mm,               // Z Thickness 
        0,                      // Starting angle
        2 * CLHEP::pi           // Ending Angle
    );

    // Define the logical volume for the end cap
    G4LogicalVolume* EndCap_Logical = new G4LogicalVolume(EndCap, Al, "EndCap_Logical");

    // Define the physical placement of the end cap (at one end of the tube)
    G4VPhysicalVolume* EndCap_Phys = new G4PVPlacement(
        0,                     // No rotation
        G4ThreeVector(0, 0, (SDD+5.08) * cm), // Placement at the end of the tube
        EndCap_Logical,        // Logical volume for the end cap
        "EndCap_Logical",      // Name of the physical volume
        logicWorld,            // Mother volume where it's placed
        false,                 // No boolean operation
        0,                     // No copy number
        true                   // Check overlaps
    );

    G4VPhysicalVolume* EndCap_Phys1 = new G4PVPlacement(
        0,                     // No rotation
        G4ThreeVector(0, 0, SDD * cm), // Placement at the end of the tube
        EndCap_Logical,        // Logical volume for the end cap
        "EndCap_Logical",      // Name of the physical volume
        logicWorld,            // Mother volume where it's placed
        false,                 // No boolean operation
        0,                     // No copy number
        true                   // Check overlaps
    );

    G4VSolid* unionSolid = new G4UnionSolid("Al_Solid+EndCap", Al_Solid, EndCap);

    /*____________________________________________________________________________________________________________________*/

    // Collimating of the source beam
    G4VSolid* leadbrick = new G4Box("LeadBrick", 3.85 * cm, 1 * cm, 4.9 * cm);
    G4LogicalVolume* leadLogical = new G4LogicalVolume(leadbrick, lead, "leadLogical");
    G4VPhysicalVolume* sheet1 = new G4PVPlacement(0, G4ThreeVector(0, 2 * cm, -0 * cm), leadLogical, "leadLogical", logicWorld, false, 0, true);
    G4VPhysicalVolume* sheet2 = new G4PVPlacement(0, G4ThreeVector(0, -2 * cm, -0 * cm), leadLogical, "leadLogical", logicWorld, false, 0, true); 
    G4VPhysicalVolume* sheet3 = new G4PVPlacement(0, G4ThreeVector(0, 0 * cm, -6 * cm), leadLogical, "leadLogical", logicWorld, false, 0, true); 
    G4VPhysicalVolume* sheet4 = new G4PVPlacement(0, G4ThreeVector(-6 * cm, 0 * cm, 0 * cm), leadLogical, "leadLogical", logicWorld, false, 0, true); 
    G4VPhysicalVolume* sheet5 = new G4PVPlacement(0, G4ThreeVector(6 * cm, 0 * cm, 0 * cm), leadLogical, "leadLogical", logicWorld, false, 0, true); 

    /*_____________________________________________________________________________________________________________________*/

    // Defining source container 
    G4Tubs *source = new G4Tubs("source",0,5*mm, 1.0*mm, 0, 2*CLHEP::pi);
    G4LogicalVolume *Logic_source = new G4LogicalVolume(source,PMMA,"Logic_source");
    G4VPhysicalVolume *source1 = new G4PVPlacement(0,G4ThreeVector(0,0,0),Logic_source, "Logic_source",logicWorld,false,0,true);

    // Create a visAttributes object with invisible settings
    G4VisAttributes* invisAttributes = new G4VisAttributes();
    invisAttributes->SetVisibility(false);

        // Assign the visAttributes to the logical volume
    logicWorld->SetVisAttributes(invisAttributes);
    NaI_Logical->SetVisAttributes(G4Color::Blue());
    MgO_Logical->SetVisAttributes(G4Color::Cyan());
    Al_Logical->SetVisAttributes(G4Color::Red());
    EndCap_Logical->SetVisAttributes(G4Color::Red());
    leadLogical->SetVisAttributes(G4VisAttributes(G4Color(0.5, 0.7, 1.0)));  // Light blue
    Logic_source->SetVisAttributes(G4VisAttributes(G4Colour(1,1,0.6,0.5)));

    return physWorld;
}
