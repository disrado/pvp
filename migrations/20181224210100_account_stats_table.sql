-- migrate:up

CREATE TABLE account_stats(
	id SERIAL NOT NULL,
	account_id INT NOT NULL,
	matches INT NOT NULL DEFAULT 0,
	wins INT NOT NULL DEFAULT 0,
	defeats INT NOT NULL DEFAULT 0,
	playtime INTERVAL NOT NULL DEFAULT '0 year 0 month 0 day 0 hour 0 minutes',
	PRIMARY KEY(id),
	FOREIGN KEY(account_id) REFERENCES account(id) ON DELETE CASCADE
);

-- migrate:down

DROP TABLE account_stats CASCADE;