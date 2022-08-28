// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACorridor.generated.h"

UCLASS()
class BENEATHTHESUN_API AACorridor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACorridor();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline", AdvancedDisplay)
	TSubclassOf<AActor> SplineActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline", AdvancedDisplay)
	FVector SplineOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", AdvancedDisplay)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", AdvancedDisplay)
	TArray<UMaterialInterface*> MaterialList;

	UPROPERTY(Transient)
	AActor* RuntimeSplineActor = nullptr;

	int8 MaterialIndex = 0;

	UWorld* World = nullptr;

protected:

	TArray<AActor*> ActorsOnCorridor;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddActorToCorridor(AActor* InActor);

	UStaticMeshComponent* GetMesh() { return StaticMesh; }

	void SetMaterialIndex(int8 index){MaterialIndex = index;}

};
