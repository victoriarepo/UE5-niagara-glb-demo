// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "TestActor.generated.h"

UCLASS()
class MYPROJECT_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* scene_root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh_component;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> static_mesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh_component2;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> static_mesh2;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* niagara_component;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* niagara_system;

};
