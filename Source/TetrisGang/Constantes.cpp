// Fill out your copyright notice in the Description page of Project Settings.


#include "Constantes.h"
#include "Engine/StaticMesh.h"




Rotations Constantes::GetRandomRotation()
{
	return Rotations(rand() % 4);
}

Pieces Constantes::GetRandomPiece()
{
	return Pieces(rand() % 7);
}

/* UStaticMesh* Constantes::GetPieceMesh(Pieces piece)
{
	UStaticMesh* mesh;
switch (piece)
	{
		case Pieces::Yelow:
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh1(TEXT("/Script/Engine.StaticMesh'/Game/Objects/pieces/boxBlock.boxBlock'"));
			 mesh = Mesh1.Object;
			break;
		case Pieces::Orange:
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh2(TEXT("/Script/Engine.StaticMesh'/Game/Objects/pieces/lBlock.lBlock'"));
			mesh = Mesh2.Object;
			break;
		case Pieces::Blue:
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh3(TEXT("/Script/Engine.StaticMesh'/Game/Objects/pieces/LvariationBlock.LvariationBlock'"));
			mesh = Mesh3.Object;
			break;
		case Pieces::Cyan:
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh4(TEXT("/Script/Engine.StaticMesh'/Game/Objects/pieces/paloBlock.paloBlock'"));
			mesh = Mesh4.Object;
			break;
		case Pieces::Green:
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh5(TEXT("/Script/Engine.StaticMesh'/Game/Objects/pieces/sBlock.sBlock'"));
			mesh = Mesh5.Object;
			break;
		case Pieces::Purple:
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh6(TEXT("/Script/Engine.StaticMesh'/Game/Objects/pieces/tBlock.tBlock'"));
			mesh = Mesh6.Object;
			break;
		case Pieces::Red:
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh7(TEXT("/Script/Engine.StaticMesh'/Game/Objects/pieces/zBlock.zBlock'"));
			mesh = Mesh7.Object;
			break;
		default:
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh8(TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));
			mesh = Mesh8.Object;
			break;
	}

	return mesh;
}*/