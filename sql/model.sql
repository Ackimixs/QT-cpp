DROP TABLE IF EXISTS public.leaderboard CASCADE;

CREATE TABLE public.leaderboard (
    id_leaderboard  SERIAL NOT NULL ,
    player          VARCHAR(50) NOT NULL default('random') ,
    score           INT NOT NULL ,
    date            TIMESTAMP NOT NULL DEFAULT now() ,
    difficulty      INT NOT NULL default(0) ,
    CONSTRAINT leaderboard_PK PRIMARY KEY (id_leaderboard)
)WITHOUT OIDS;