-- migrate:up

CREATE TABLE ability(
	id SERIAL NOT NULL,
	name TEXT NOT NULL,
	damage INT NOT NULL,
	description TEXT NOT NULL DEFAULT '',
	PRIMARY KEY(id),
	UNIQUE(name)
);

-- migrate:down

DROP TABLE ability CASCADE;