-- migrate:up

CREATE TABLE account_setting(
	id SERIAL NOT NULL,
	account_id INT NOT NULL,
	rezolution TEXT NOT NULL DEFAULT '1920x1080',
	volume INT NOT NULL DEFAULT 50,
	keybindings TEXT NOT NULL,
	PRIMARY KEY(id),
	FOREIGN KEY(account_id) REFERENCES account(id) ON DELETE CASCADE
);

-- migrate:down

DROP TABLE account_setting CASCADE;