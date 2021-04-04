static const u16 sTutorMoves[MOVETUTOR_COUNT] =
{
    [MOVETUTOR_MEGA_PUNCH] = MOVE_MEGA_PUNCH,
    [MOVETUTOR_SWORDS_DANCE] = MOVE_SWORDS_DANCE,
    [MOVETUTOR_MEGA_KICK] = MOVE_MEGA_KICK,
    [MOVETUTOR_BODY_SLAM] = MOVE_BODY_SLAM,
    [MOVETUTOR_DOUBLE_EDGE] = MOVE_DOUBLE_EDGE,
    [MOVETUTOR_COUNTER] = MOVE_COUNTER,
    [MOVETUTOR_SEISMIC_TOSS] = MOVE_SEISMIC_TOSS,
    [MOVETUTOR_MIMIC] = MOVE_MIMIC,
    [MOVETUTOR_METRONOME] = MOVE_METRONOME,
    [MOVETUTOR_SOFT_BOILED] = MOVE_SOFT_BOILED,
    [MOVETUTOR_DREAM_EATER] = MOVE_DREAM_EATER,
    [MOVETUTOR_THUNDER_WAVE] = MOVE_THUNDER_WAVE,
    [MOVETUTOR_EXPLOSION] = MOVE_EXPLOSION,
    [MOVETUTOR_ROCK_SLIDE] = MOVE_ROCK_SLIDE,
    [MOVETUTOR_SUBSTITUTE] = MOVE_SUBSTITUTE,
};

#define TUTOR(move) (1 << (MOVETUTOR_##move))

static const u16 sTutorLearnsets[] =
{
    [SPECIES_NONE] = 0,

    [SPECIES_BULBASAUR] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_IVYSAUR] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_VENUSAUR] = TUTOR(SWORDS_DANCE)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_CHARMANDER] = TUTOR(MEGA_PUNCH)
                         | TUTOR(SWORDS_DANCE)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(ROCK_SLIDE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_CHARMELEON] = TUTOR(MEGA_PUNCH)
                         | TUTOR(SWORDS_DANCE)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(ROCK_SLIDE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_CHARIZARD] = TUTOR(MEGA_PUNCH)
                        | TUTOR(SWORDS_DANCE)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_SQUIRTLE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_WARTORTLE] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_BLASTOISE] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_CATERPIE] = 0,

    [SPECIES_METAPOD] = 0,

    [SPECIES_BUTTERFREE] = TUTOR(DOUBLE_EDGE)
                         | TUTOR(MIMIC)
                         | TUTOR(DREAM_EATER)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_WEEDLE] = 0,

    [SPECIES_KAKUNA] = 0,

    [SPECIES_BEEDRILL] = TUTOR(SWORDS_DANCE)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_PIDGEY] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_PIDGEOTTO] = TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_PIDGEOT] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_RATTATA] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_RATICATE] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SPEAROW] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_FEAROW] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_EKANS] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(ROCK_SLIDE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_ARBOK] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(ROCK_SLIDE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_PIKACHU] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_RAICHU] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_SANDSHREW] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_SANDSLASH] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_NIDORAN_F] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_NIDORINA] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_NIDOQUEEN] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_NIDORAN_M] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_NIDORINO] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_NIDOKING] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_CLEFAIRY] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(SOFT_BOILED)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_CLEFABLE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(SOFT_BOILED)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_VULPIX] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_NINETALES] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_JIGGLYPUFF] = TUTOR(MEGA_PUNCH)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(DREAM_EATER)
                         | TUTOR(THUNDER_WAVE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_WIGGLYTUFF] = TUTOR(MEGA_PUNCH)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(DREAM_EATER)
                         | TUTOR(THUNDER_WAVE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_ZUBAT] = TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_GOLBAT] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_ODDISH] = TUTOR(SWORDS_DANCE)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_GLOOM] = TUTOR(SWORDS_DANCE)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_VILEPLUME] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_PARAS] = TUTOR(SWORDS_DANCE)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(COUNTER)
                    | TUTOR(MIMIC)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_PARASECT] = TUTOR(SWORDS_DANCE)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_VENONAT] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_VENOMOTH] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_DIGLETT] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_DUGTRIO] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_MEOWTH] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_PERSIAN] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_PSYDUCK] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_GOLDUCK] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_MANKEY] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_PRIMEAPE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_GROWLITHE] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_ARCANINE] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_POLIWAG] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_POLIWHIRL] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(METRONOME)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_POLIWRATH] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(METRONOME)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_ABRA] = TUTOR(MEGA_PUNCH)
                   | TUTOR(MEGA_KICK)
                   | TUTOR(BODY_SLAM)
                   | TUTOR(DOUBLE_EDGE)
                   | TUTOR(COUNTER)
                   | TUTOR(SEISMIC_TOSS)
                   | TUTOR(MIMIC)
                   | TUTOR(METRONOME)
                   | TUTOR(DREAM_EATER)
                   | TUTOR(THUNDER_WAVE)
                   | TUTOR(SUBSTITUTE),

    [SPECIES_KADABRA] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_ALAKAZAM] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_MACHOP] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MACHOKE] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_MACHAMP] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_BELLSPROUT] = TUTOR(SWORDS_DANCE)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(MIMIC)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_WEEPINBELL] = TUTOR(SWORDS_DANCE)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(MIMIC)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_VICTREEBEL] = TUTOR(SWORDS_DANCE)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(MIMIC)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_TENTACOOL] = TUTOR(SWORDS_DANCE)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_TENTACRUEL] = TUTOR(SWORDS_DANCE)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(MIMIC)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_GEODUDE] = TUTOR(MEGA_PUNCH)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(EXPLOSION)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_GRAVELER] = TUTOR(MEGA_PUNCH)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(EXPLOSION)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_GOLEM] = TUTOR(MEGA_PUNCH)
                    | TUTOR(MEGA_KICK)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(COUNTER)
                    | TUTOR(SEISMIC_TOSS)
                    | TUTOR(MIMIC)
                    | TUTOR(METRONOME)
                    | TUTOR(EXPLOSION)
                    | TUTOR(ROCK_SLIDE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_PONYTA] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_RAPIDASH] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SLOWPOKE] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SLOWBRO] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_MAGNEMITE] = TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_MAGNETON] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_FARFETCHD] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_DODUO] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_DODRIO] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_SEEL] = TUTOR(BODY_SLAM)
                   | TUTOR(DOUBLE_EDGE)
                   | TUTOR(MIMIC)
                   | TUTOR(SUBSTITUTE),

    [SPECIES_DEWGONG] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_GRIMER] = TUTOR(BODY_SLAM)
                     | TUTOR(MIMIC)
                     | TUTOR(EXPLOSION)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MUK] = TUTOR(BODY_SLAM)
                  | TUTOR(MIMIC)
                  | TUTOR(EXPLOSION)
                  | TUTOR(SUBSTITUTE),

    [SPECIES_SHELLDER] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(EXPLOSION)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_CLOYSTER] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(EXPLOSION)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_GASTLY] = TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(EXPLOSION)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_HAUNTER] = TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(EXPLOSION)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_GENGAR] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(EXPLOSION)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_ONIX] = TUTOR(BODY_SLAM)
                   | TUTOR(DOUBLE_EDGE)
                   | TUTOR(MIMIC)
                   | TUTOR(EXPLOSION)
                   | TUTOR(ROCK_SLIDE)
                   | TUTOR(SUBSTITUTE),

    [SPECIES_DROWZEE] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_HYPNO] = TUTOR(MEGA_PUNCH)
                    | TUTOR(MEGA_KICK)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(COUNTER)
                    | TUTOR(SEISMIC_TOSS)
                    | TUTOR(MIMIC)
                    | TUTOR(METRONOME)
                    | TUTOR(DREAM_EATER)
                    | TUTOR(THUNDER_WAVE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_KRABBY] = TUTOR(SWORDS_DANCE)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_KINGLER] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_VOLTORB] = TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(EXPLOSION)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_ELECTRODE] = TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(EXPLOSION)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_EXEGGCUTE] = TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(DREAM_EATER)
                        | TUTOR(EXPLOSION)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_EXEGGUTOR] = TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(DREAM_EATER)
                        | TUTOR(EXPLOSION)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_CUBONE] = TUTOR(MEGA_PUNCH)
                     | TUTOR(SWORDS_DANCE)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MAROWAK] = TUTOR(MEGA_PUNCH)
                      | TUTOR(SWORDS_DANCE)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_HITMONLEE] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(METRONOME)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_HITMONCHAN] = TUTOR(MEGA_PUNCH)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(METRONOME)
                         | TUTOR(ROCK_SLIDE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_LICKITUNG] = TUTOR(MEGA_PUNCH)
                        | TUTOR(SWORDS_DANCE)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(DREAM_EATER)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_KOFFING] = TUTOR(MIMIC)
                      | TUTOR(EXPLOSION)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_WEEZING] = TUTOR(MIMIC)
                      | TUTOR(EXPLOSION)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_RHYHORN] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_RHYDON] = TUTOR(MEGA_PUNCH)
                     | TUTOR(SWORDS_DANCE)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_CHANSEY] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(SOFT_BOILED)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_TANGELA] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_KANGASKHAN] = TUTOR(MEGA_PUNCH)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(ROCK_SLIDE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_HORSEA] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_SEADRA] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_GOLDEEN] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SEAKING] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_STARYU] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_STARMIE] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_MR_MIME] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SCYTHER] = TUTOR(SWORDS_DANCE)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_JYNX] = TUTOR(MEGA_PUNCH)
                   | TUTOR(MEGA_KICK)
                   | TUTOR(BODY_SLAM)
                   | TUTOR(DOUBLE_EDGE)
                   | TUTOR(COUNTER)
                   | TUTOR(SEISMIC_TOSS)
                   | TUTOR(MIMIC)
                   | TUTOR(METRONOME)
                   | TUTOR(DREAM_EATER)
                   | TUTOR(SUBSTITUTE),

    [SPECIES_ELECTABUZZ] = TUTOR(MEGA_PUNCH)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(THUNDER_WAVE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_MAGMAR] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_PINSIR] = TUTOR(SWORDS_DANCE)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_TAUROS] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MAGIKARP] = 0,

    [SPECIES_GYARADOS] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_LAPRAS] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_DITTO] = 0,

    [SPECIES_EEVEE] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_VAPOREON] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_JOLTEON] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_FLAREON] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_PORYGON] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_OMANYTE] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_OMASTAR] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_KABUTO] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_KABUTOPS] = TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_AERODACTYL] = TUTOR(DOUBLE_EDGE)
                         | TUTOR(MIMIC)
                         | TUTOR(ROCK_SLIDE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_SNORLAX] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_ARTICUNO] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_ZAPDOS] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MOLTRES] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_DRATINI] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_DRAGONAIR] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_DRAGONITE] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_MEWTWO] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MEW] = TUTOR(MEGA_PUNCH)
                  | TUTOR(SWORDS_DANCE)
                  | TUTOR(MEGA_KICK)
                  | TUTOR(BODY_SLAM)
                  | TUTOR(DOUBLE_EDGE)
                  | TUTOR(COUNTER)
                  | TUTOR(SEISMIC_TOSS)
                  | TUTOR(MIMIC)
                  | TUTOR(METRONOME)
                  | TUTOR(SOFT_BOILED)
                  | TUTOR(DREAM_EATER)
                  | TUTOR(THUNDER_WAVE)
                  | TUTOR(EXPLOSION)
                  | TUTOR(ROCK_SLIDE)
                  | TUTOR(SUBSTITUTE),

    [SPECIES_CHIKORITA] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_BAYLEEF] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_MEGANIUM] = TUTOR(SWORDS_DANCE)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_CYNDAQUIL] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_QUILAVA] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_TYPHLOSION] = TUTOR(MEGA_PUNCH)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(ROCK_SLIDE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_TOTODILE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_CROCONAW] = TUTOR(MEGA_PUNCH)
                       | TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_FERALIGATR] = TUTOR(MEGA_PUNCH)
                         | TUTOR(SWORDS_DANCE)
                         | TUTOR(MEGA_KICK)
                         | TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(SEISMIC_TOSS)
                         | TUTOR(MIMIC)
                         | TUTOR(ROCK_SLIDE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_SENTRET] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_FURRET] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_HOOTHOOT] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_NOCTOWL] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_LEDYBA] = TUTOR(MEGA_PUNCH)
                     | TUTOR(SWORDS_DANCE)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_LEDIAN] = TUTOR(MEGA_PUNCH)
                     | TUTOR(SWORDS_DANCE)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_SPINARAK] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_ARIADOS] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_CROBAT] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_CHINCHOU] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_LANTURN] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_PICHU] = TUTOR(MEGA_PUNCH)
                    | TUTOR(MEGA_KICK)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(COUNTER)
                    | TUTOR(SEISMIC_TOSS)
                    | TUTOR(MIMIC)
                    | TUTOR(THUNDER_WAVE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_CLEFFA] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(SOFT_BOILED)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_IGGLYBUFF] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(DREAM_EATER)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_TOGEPI] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(SOFT_BOILED)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_TOGETIC] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(SOFT_BOILED)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_NATU] = TUTOR(DOUBLE_EDGE)
                   | TUTOR(MIMIC)
                   | TUTOR(DREAM_EATER)
                   | TUTOR(THUNDER_WAVE)
                   | TUTOR(SUBSTITUTE),

    [SPECIES_XATU] = TUTOR(DOUBLE_EDGE)
                   | TUTOR(MIMIC)
                   | TUTOR(DREAM_EATER)
                   | TUTOR(THUNDER_WAVE)
                   | TUTOR(SUBSTITUTE),

    [SPECIES_MAREEP] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_FLAAFFY] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_AMPHAROS] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_BELLOSSOM] = TUTOR(SWORDS_DANCE)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_MARILL] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_AZUMARILL] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_SUDOWOODO] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(EXPLOSION)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_POLITOED] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_HOPPIP] = TUTOR(SWORDS_DANCE)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_SKIPLOOM] = TUTOR(SWORDS_DANCE)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_JUMPLUFF] = TUTOR(SWORDS_DANCE)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_AIPOM] = TUTOR(MEGA_PUNCH)
                    | TUTOR(MEGA_KICK)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(COUNTER)
                    | TUTOR(SEISMIC_TOSS)
                    | TUTOR(MIMIC)
                    | TUTOR(METRONOME)
                    | TUTOR(DREAM_EATER)
                    | TUTOR(THUNDER_WAVE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_SUNKERN] = TUTOR(SWORDS_DANCE)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SUNFLORA] = TUTOR(SWORDS_DANCE)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_YANMA] = TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(DREAM_EATER)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_WOOPER] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_QUAGSIRE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_ESPEON] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_UMBREON] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_MURKROW] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SLOWKING] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_MISDREAVUS] = TUTOR(DOUBLE_EDGE)
                         | TUTOR(MIMIC)
                         | TUTOR(DREAM_EATER)
                         | TUTOR(THUNDER_WAVE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_UNOWN] = 0,

    [SPECIES_WOBBUFFET] = 0,

    [SPECIES_GIRAFARIG] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(DREAM_EATER)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_PINECO] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(MIMIC)
                     | TUTOR(EXPLOSION)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_FORRETRESS] = TUTOR(BODY_SLAM)
                         | TUTOR(DOUBLE_EDGE)
                         | TUTOR(COUNTER)
                         | TUTOR(MIMIC)
                         | TUTOR(EXPLOSION)
                         | TUTOR(ROCK_SLIDE)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_DUNSPARCE] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(MIMIC)
                        | TUTOR(DREAM_EATER)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_GLIGAR] = TUTOR(SWORDS_DANCE)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_STEELIX] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(EXPLOSION)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SNUBBULL] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_GRANBULL] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_QWILFISH] = TUTOR(SWORDS_DANCE)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SCIZOR] = TUTOR(SWORDS_DANCE)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_SHUCKLE] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_HERACROSS] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_SNEASEL] = TUTOR(SWORDS_DANCE)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_TEDDIURSA] = TUTOR(MEGA_PUNCH)
                        | TUTOR(SWORDS_DANCE)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(METRONOME)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_URSARING] = TUTOR(MEGA_PUNCH)
                       | TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SLUGMA] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MAGCARGO] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SWINUB] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_PILOSWINE] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_CORSOLA] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(EXPLOSION)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_REMORAID] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_OCTILLERY] = TUTOR(DOUBLE_EDGE)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_DELIBIRD] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_MANTINE] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SKARMORY] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_HOUNDOUR] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_HOUNDOOM] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_KINGDRA] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_PHANPY] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_DONPHAN] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_PORYGON2] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_STANTLER] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SMEARGLE] = 0,

    [SPECIES_TYROGUE] = TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_HITMONTOP] = TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_SMOOCHUM] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_ELEKID] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MAGBY] = TUTOR(MEGA_PUNCH)
                    | TUTOR(MEGA_KICK)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(COUNTER)
                    | TUTOR(SEISMIC_TOSS)
                    | TUTOR(MIMIC)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_MILTANK] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_BLISSEY] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(SOFT_BOILED)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_RAIKOU] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_ENTEI] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_SUICUNE] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_LARVITAR] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_PUPITAR] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_TYRANITAR] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_LUGIA] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(DREAM_EATER)
                    | TUTOR(THUNDER_WAVE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_HO_OH] = TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(DREAM_EATER)
                    | TUTOR(THUNDER_WAVE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_CELEBI] = TUTOR(SWORDS_DANCE)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_TREECKO] = TUTOR(MEGA_PUNCH)
                      | TUTOR(SWORDS_DANCE)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_GROVYLE] = TUTOR(MEGA_PUNCH)
                      | TUTOR(SWORDS_DANCE)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SCEPTILE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_TORCHIC] = TUTOR(MEGA_PUNCH)
                      | TUTOR(SWORDS_DANCE)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_COMBUSKEN] = TUTOR(MEGA_PUNCH)
                        | TUTOR(SWORDS_DANCE)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_BLAZIKEN] = TUTOR(MEGA_PUNCH)
                       | TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_MUDKIP] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MARSHTOMP] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_SWAMPERT] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_POOCHYENA] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_MIGHTYENA] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_ZIGZAGOON] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_LINOONE] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_WURMPLE] = 0,

    [SPECIES_SILCOON] = 0,

    [SPECIES_BEAUTIFLY] = TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_CASCOON] = 0,

    [SPECIES_DUSTOX] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_LOTAD] = TUTOR(SWORDS_DANCE)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_LOMBRE] = TUTOR(SWORDS_DANCE)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_LUDICOLO] = TUTOR(MEGA_PUNCH)
                       | TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SEEDOT] = TUTOR(SWORDS_DANCE)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(EXPLOSION)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_NUZLEAF] = TUTOR(SWORDS_DANCE)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(EXPLOSION)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SHIFTRY] = TUTOR(SWORDS_DANCE)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(EXPLOSION)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_NINCADA] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_NINJASK] = TUTOR(SWORDS_DANCE)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SHEDINJA] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_TAILLOW] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SWELLOW] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SHROOMISH] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_BRELOOM] = TUTOR(MEGA_PUNCH)
                      | TUTOR(SWORDS_DANCE)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SPINDA] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_WINGULL] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_PELIPPER] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SURSKIT] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_MASQUERAIN] = TUTOR(DOUBLE_EDGE)
                         | TUTOR(MIMIC)
                         | TUTOR(SUBSTITUTE),

    [SPECIES_WAILMER] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_WAILORD] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SKITTY] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_DELCATTY] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_KECLEON] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_BALTOY] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(EXPLOSION)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_CLAYDOL] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(EXPLOSION)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_NOSEPASS] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(EXPLOSION)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_TORKOAL] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(EXPLOSION)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SABLEYE] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_BARBOACH] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_WHISCASH] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_LUVDISC] = TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_CORPHISH] = TUTOR(SWORDS_DANCE)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_CRAWDAUNT] = TUTOR(SWORDS_DANCE)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(MIMIC)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_FEEBAS] = TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MILOTIC] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_CARVANHA] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SHARPEDO] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_TRAPINCH] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_VIBRAVA] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_FLYGON] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MAKUHITA] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_HARIYAMA] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_ELECTRIKE] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_MANECTRIC] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_NUMEL] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(ROCK_SLIDE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_CAMERUPT] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(EXPLOSION)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SPHEAL] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_SEALEO] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_WALREIN] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_CACNEA] = TUTOR(MEGA_PUNCH)
                     | TUTOR(SWORDS_DANCE)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_CACTURNE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SNORUNT] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_GLALIE] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(EXPLOSION)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_LUNATONE] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(EXPLOSION)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SOLROCK] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(EXPLOSION)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_AZURILL] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SPOINK] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_GRUMPIG] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_PLUSLE] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(METRONOME)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MINUN] = TUTOR(MEGA_PUNCH)
                    | TUTOR(MEGA_KICK)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(COUNTER)
                    | TUTOR(SEISMIC_TOSS)
                    | TUTOR(MIMIC)
                    | TUTOR(METRONOME)
                    | TUTOR(THUNDER_WAVE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_MAWILE] = TUTOR(MEGA_PUNCH)
                     | TUTOR(SWORDS_DANCE)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_MEDITITE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_MEDICHAM] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SWABLU] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_ALTARIA] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_WYNAUT] = 0,

    [SPECIES_DUSKULL] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_DUSCLOPS] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_ROSELIA] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SLAKOTH] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_VIGOROTH] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_SLAKING] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_GULPIN] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(EXPLOSION)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_SWALOT] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(EXPLOSION)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_TROPIUS] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_WHISMUR] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_LOUDRED] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_EXPLOUD] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_CLAMPERL] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_HUNTAIL] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_GOREBYSS] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_ABSOL] = TUTOR(SWORDS_DANCE)
                    | TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(COUNTER)
                    | TUTOR(MIMIC)
                    | TUTOR(DREAM_EATER)
                    | TUTOR(THUNDER_WAVE)
                    | TUTOR(ROCK_SLIDE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_SHUPPET] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_BANETTE] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SEVIPER] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_ZANGOOSE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(SWORDS_DANCE)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_RELICANTH] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_ARON] = TUTOR(BODY_SLAM)
                   | TUTOR(DOUBLE_EDGE)
                   | TUTOR(MIMIC)
                   | TUTOR(ROCK_SLIDE)
                   | TUTOR(SUBSTITUTE),

    [SPECIES_LAIRON] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_AGGRON] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_CASTFORM] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_VOLBEAT] = TUTOR(MEGA_PUNCH)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_ILLUMISE] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(METRONOME)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_LILEEP] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_CRADILY] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_ANORITH] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_ARMALDO] = TUTOR(SWORDS_DANCE)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_RALTS] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(DREAM_EATER)
                    | TUTOR(THUNDER_WAVE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_KIRLIA] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_GARDEVOIR] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(DREAM_EATER)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_BAGON] = TUTOR(BODY_SLAM)
                    | TUTOR(DOUBLE_EDGE)
                    | TUTOR(MIMIC)
                    | TUTOR(ROCK_SLIDE)
                    | TUTOR(SUBSTITUTE),

    [SPECIES_SHELGON] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_SALAMENCE] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_BELDUM] = 0,

    [SPECIES_METANG] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(EXPLOSION)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_METAGROSS] = TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(MIMIC)
                        | TUTOR(EXPLOSION)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_REGIROCK] = TUTOR(MEGA_PUNCH)
                       | TUTOR(MEGA_KICK)
                       | TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(COUNTER)
                       | TUTOR(SEISMIC_TOSS)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(EXPLOSION)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_REGICE] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(EXPLOSION)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_REGISTEEL] = TUTOR(MEGA_PUNCH)
                        | TUTOR(MEGA_KICK)
                        | TUTOR(BODY_SLAM)
                        | TUTOR(DOUBLE_EDGE)
                        | TUTOR(COUNTER)
                        | TUTOR(SEISMIC_TOSS)
                        | TUTOR(MIMIC)
                        | TUTOR(THUNDER_WAVE)
                        | TUTOR(EXPLOSION)
                        | TUTOR(ROCK_SLIDE)
                        | TUTOR(SUBSTITUTE),

    [SPECIES_KYOGRE] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_GROUDON] = TUTOR(MEGA_PUNCH)
                      | TUTOR(SWORDS_DANCE)
                      | TUTOR(MEGA_KICK)
                      | TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(COUNTER)
                      | TUTOR(SEISMIC_TOSS)
                      | TUTOR(MIMIC)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(ROCK_SLIDE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_RAYQUAZA] = TUTOR(BODY_SLAM)
                       | TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(THUNDER_WAVE)
                       | TUTOR(ROCK_SLIDE)
                       | TUTOR(SUBSTITUTE),

    [SPECIES_LATIAS] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_LATIOS] = TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_JIRACHI] = TUTOR(BODY_SLAM)
                      | TUTOR(DOUBLE_EDGE)
                      | TUTOR(MIMIC)
                      | TUTOR(METRONOME)
                      | TUTOR(DREAM_EATER)
                      | TUTOR(THUNDER_WAVE)
                      | TUTOR(SUBSTITUTE),

    [SPECIES_DEOXYS] = TUTOR(MEGA_PUNCH)
                     | TUTOR(MEGA_KICK)
                     | TUTOR(BODY_SLAM)
                     | TUTOR(DOUBLE_EDGE)
                     | TUTOR(COUNTER)
                     | TUTOR(SEISMIC_TOSS)
                     | TUTOR(MIMIC)
                     | TUTOR(DREAM_EATER)
                     | TUTOR(THUNDER_WAVE)
                     | TUTOR(ROCK_SLIDE)
                     | TUTOR(SUBSTITUTE),

    [SPECIES_CHIMECHO] = TUTOR(DOUBLE_EDGE)
                       | TUTOR(MIMIC)
                       | TUTOR(DREAM_EATER)
                       | TUTOR(SUBSTITUTE),
};
