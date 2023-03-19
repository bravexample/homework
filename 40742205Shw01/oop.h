#ifndef OOP_H
#define OOP_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum MagicalEffect { 
    EFF_Haste = 0,
    EFF_Slowness,
    EFF_Hunger,
    EFF_Saturation
};

static const char *MagicalEffectToString[] = {
    "Haste",
    "Slowness",
    "Hunger",
    "Saturation",
};

struct Potato {
    void (*print)(const struct Potato *);
    // Destruct potato and turn it into potato ball
    struct PotatoBall *(*fry)(struct Potato **);
    int32_t weight;
    const char *producer_name;
};

struct MagicalPotato {
    struct Potato base;
    enum MagicalEffect effect;
    int effect_level;
};

struct PotatoBall {
    void (*print)(const struct PotatoBall *);
    void (*dtor)(struct PotatoBall **);
    const char *producer_name;
    int32_t weight;
};

struct MagicalPotatoBall {
    struct PotatoBall base;
    enum MagicalEffect effect;
    int effect_level;
};

/*
 Potato farmer or summoner
*/
struct PotatoProducer {
    struct Potato *(*produce)(const struct PotatoProducer *);
    char name[32];
};

void print_potato(const struct Potato *this) {
    printf("Potato:\n\tweight: %d\n\tproduced by: %s\n",
            this->weight, this->producer_name);
}
void print_magical_potato(const struct Potato *this) {
    const struct MagicalPotato *temp = (const struct MagicalPotato *)this;
    printf("Magical Potato:\n\tweight: %d\n\tproduced by: %s\n\tmagical effect: %s\n\tmagic level: %d\n",
            temp->base.weight, temp->base.producer_name, MagicalEffectToString[temp->effect], temp->effect_level);
}
void potato_dtor(struct Potato **obj) {
    free(*obj);
    *obj = NULL;
}
void magical_potato_dtor(struct Potato **obj) {
    free(*obj);
    *obj = NULL;
}

void print_potato_ball(const struct PotatoBall *this) {
    printf("Potato Ball:\n\tweight: %d\n\tproduced by: %s\n",
            this->weight, this->producer_name);
}
void print_magical_potato_ball(const struct PotatoBall *this) {
    const struct MagicalPotatoBall *temp = (const struct MagicalPotatoBall *)this;
    printf("Magical Potato Ball:\n\tweight: %d\n\tproduced by: %s\n\tmagical effect: %s\n\tmagic level: %d\n",
            temp->base.weight, temp->base.producer_name, MagicalEffectToString[temp->effect], temp->effect_level);
}
void potato_ball_dtor(struct PotatoBall **obj) {
    free(*obj);
    *obj = NULL;
}
void magical_potato_ball_dtor(struct PotatoBall **obj) {
    free(*obj);
    *obj = NULL;
}

struct PotatoBall *fry_potato_ball(struct Potato **input) {
    struct PotatoBall *potatoBall = malloc(sizeof(struct PotatoBall));
    potatoBall->print             = print_potato_ball;
    potatoBall->dtor              = potato_ball_dtor;
    potatoBall->producer_name     = (*input)->producer_name;
    potatoBall->weight            = (*input)->weight + (rand() % 100);
    free(*input);
    *input = NULL;
    return potatoBall;
}
struct PotatoBall *fry_magical_potato_ball(struct Potato **input) {
    struct MagicalPotato **temp = (struct MagicalPotato **)input;
    struct MagicalPotatoBall *potatoBall = malloc(sizeof(struct MagicalPotatoBall));
    potatoBall->base.print               = print_magical_potato_ball;
    potatoBall->base.dtor                = magical_potato_ball_dtor;
    potatoBall->base.producer_name       = (*temp)->base.producer_name;
    potatoBall->base.weight              = (*temp)->base.weight + (rand() % 200);
    potatoBall->effect                   = (*temp)->effect;
    potatoBall->effect_level             = (*temp)->effect_level + (rand() % 100);
    free(*temp);
    *temp = NULL;
    return (struct PotatoBall *)potatoBall;
}

struct Potato *smallten_summon_potato(const struct PotatoProducer *this) {
    struct MagicalPotato *potato = malloc(sizeof(struct MagicalPotato));
    potato->base.print           = print_magical_potato;
    potato->base.fry             = fry_magical_potato_ball;
    potato->base.weight          = (rand() % 100) + 500;
    potato->base.producer_name   = this->name;
    potato->effect               = rand() % 4;
    potato->effect_level         = rand() % 100;
    return (struct Potato *)potato;
}
struct Potato *subarya_produce_potato(const struct PotatoProducer *this) {
    struct Potato *potato = malloc(sizeof(struct Potato));
    potato->print         = print_potato;
    potato->fry           = fry_potato_ball;
    potato->weight        = (rand() % 100) + 300;
    potato->producer_name = this->name;
    return potato;
}

void init_smallten(struct PotatoProducer *obj) {
    obj->produce = smallten_summon_potato;
    char *producer = "Smallten";
    size_t i = 0;
    for (; producer[i]; i++)
        obj->name[i] = producer[i];
    obj->name[i] = '\0';
    srand(time(NULL));
}
void init_subarya(struct PotatoProducer *obj) {
    obj->produce = subarya_produce_potato;
    char *producer = "Subarya";
    size_t i = 0;
    for (; producer[i]; i++)
        obj->name[i] = producer[i];
    obj->name[i] = '\0';
    srand(time(NULL));
}

#endif