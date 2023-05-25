DROP TABLE IF EXISTS public.leaderboard CASCADE;
DROP TABLE IF EXISTS public.player CASCADE;

CREATE TABLE public.player (
    username        VARCHAR(50) NOT NULL default('random'),
    CONSTRAINT player_PK PRIMARY KEY (username)
)WITHOUT OIDS;

CREATE TABLE public.leaderboard (
    id_leaderboard  SERIAL NOT NULL ,
    player          VARCHAR(50) NOT NULL ,
    score           INT NOT NULL ,
    date            TIMESTAMP NOT NULL DEFAULT now() ,
    CONSTRAINT leaderboard_PK PRIMARY KEY (id_leaderboard),
    CONSTRAINT leaderboard_FK FOREIGN KEY (player) REFERENCES public.player(username)
)WITHOUT OIDS;