CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(40) NOT NULL,
    password VARCHAR(40) NOT NULL,
    first_name VARCHAR(40),
    last_name VARCHAR(40),
    email VARCHAR(255),
    phone VARCHAR(16),
    avatar_url TEXT,
    is_online BOOLEAN DEFAULT 0,
    last_time_online DATETIME,
    url_to_profile TEXT,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP,
    CONSTRAINT uc_users_username UNIQUE (username)
);

CREATE TABLE IF NOT EXISTS chats (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(40),
    description VARCHAR(255),
    type ENUM('private', 'group', 'channel'),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP
);

CREATE TABLE IF NOT EXISTS chat_users (
    chat_id INT NOT NULL,
    user_id INT NOT NULL,
    role ENUM('owner', 'admin', 'user'),
    joined_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    left_at TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    CONSTRAINT pk_chat_users PRIMARY KEY (user_id, chat_id),
    CONSTRAINT fk_chat_users_user_id FOREIGN KEY (user_id) REFERENCES users(id),
    CONSTRAINT fk_chat_users_chat_id FOREIGN KEY (chat_id) REFERENCES chats(id)
);

CREATE TABLE IF NOT EXISTS messages (
    id INT AUTO_INCREMENT PRIMARY KEY,
    chat_id INT NOT NULL,
    sender_id INT NOT NULL,
    reply_to_id INT,
    text VARCHAR(255) NOT NULL,
    is_edited BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    CONSTRAINT fk_messages_sender_id FOREIGN KEY (sender_id) REFERENCES users(id),
    CONSTRAINT fk_messages_chat_id FOREIGN KEY (chat_id) REFERENCES chats(id),
    CONSTRAINT fk_messages_reply_to_id FOREIGN KEY (reply_to_id) REFERENCES messages(id)
);

CREATE TABLE IF NOT EXISTS message_deletions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    message_id INTEGER,
    deleted_for_user_id INT,
    deleted_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_message_deletions_message_id FOREIGN KEY (message_id) REFERENCES messages(id),
    CONSTRAINT fk_message_deletions_deleted_for_user_id FOREIGN KEY (deleted_for_user_id) REFERENCES users(id)
);


CREATE TABLE IF NOT EXISTS message_reads (
    id INT NOT NULL,
    message_id INT NOT NULL,
    user_id INT NOT NULL,
    read_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_message_reads PRIMARY KEY (user_id, message_id),
    CONSTRAINT fk_message_reads_user_id FOREIGN KEY (user_id) REFERENCES users(id),
    CONSTRAINT fk_message_reads_message_id FOREIGN KEY (message_id) REFERENCES messages(id)
);
