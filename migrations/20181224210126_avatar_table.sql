-- migrate:up

CREATE TABLE avatar(
	id SERIAL NOT NULL,
	account_id INT NOT NULL,
	class_id INT NOT NULL,
	name TEXT NOT NULL,
	lvl INT NOT NULL DEFAULT 0,
	playtime INTERVAL NOT NULL DEFAULT '0 year 0 month 0 day 0 hour 0 minutes',
	PRIMARY KEY(id),
	FOREIGN KEY(class_id) REFERENCES class(id) ON DELETE CASCADE,
	FOREIGN KEY(account_id) REFERENCES account(id) ON DELETE CASCADE,
	UNIQUE(name)
);

-- migrate:down

DROP TABLE avatar CASCADE;