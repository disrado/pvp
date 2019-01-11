-- migrate:up

CREATE TABLE account(
	id SERIAL NOT NULL,
	email TEXT NOT NULL,
	password TEXT NOT NULL,
	question TEXT NOT NULL,
	answer TEXT NOT NULL,
	name TEXT NOT NULL,
	created_at TIMESTAMP NOT NULL,
	login_at TIMESTAMP NOT NULL,
	status_2fa BOOLEAN NOT NULL,
	status TEXT NOT NULL,
	PRIMARY KEY(id),
	UNIQUE(email)
);

-- migrate:down

DROP TABLE account CASCADE;