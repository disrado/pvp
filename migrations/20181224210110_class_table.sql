-- migrate:up

CREATE TABLE class(
	id SERIAL NOT NULL,
	abilities TEXT NOT NULL DEFAULT '',
	hp INT NOT NULL,
	mp INT NOT NULL,
	PRIMARY KEY(id)
);

-- migrate:down

DROP TABLE class CASCADE;