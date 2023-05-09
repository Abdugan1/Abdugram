CREATE TABLE IF NOT EXISTS users (
  id INTEGER PRIMARY KEY,
  username TEXT UNIQUE,
  first_name TEXT,
  last_name TEXT,
  email TEXT UNIQUE,
  phone TEXT,
  avatar_url TEXT,
  created_at DATETIME,
  updated_at DATETIME,
  last_time_online DATETIME,
  is_online INTEGER,
  is_deleted INTEGER
);

CREATE TABLE IF NOT EXISTS chats (
  id INTEGER PRIMARY KEY,
  name TEXT,
  description TEXT,
  type TEXT CHECK(type IN ('private', 'group', 'channel')),
  created_at DATETIME,
  updated_at DATETIME,
  deleted_at DATETIME,
  is_deleted INTEGER
);

CREATE TABLE IF NOT EXISTS chat_users (
  chat_id INTEGER,
  user_id INTEGER,
  role TEXT CHECK (role IN('admin', 'user')),
  joined_at DATETIME,
  left_at DATETIME,
  PRIMARY KEY (chat_id, user_id),
  FOREIGN KEY (chat_id) REFERENCES chats(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS messages (
  id INTEGER PRIMARY KEY,
  chat_id INTEGER,
  sender_id INTEGER,
  reply_to_id INTEGER,
  text TEXT,
  is_edited INTEGER,
  created_at DATETIME,
  updated_at DATETIME,
  FOREIGN KEY (chat_id) REFERENCES chats(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (sender_id) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (reply_to_id) REFERENCES messages(id) ON DELETE CASCADE ON UPDATE CASCADE
);


CREATE TABLE IF NOT EXISTS message_deletions (
  id INTEGER PRIMARY KEY,
  message_id INTEGER,
  deleter_id INTEGER,
  deleted_at DATETIME,
  FOREIGN KEY (message_id) REFERENCES messages(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (deleter_id) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS message_reads (
  id INTEGER PRIMARY KEY,
  message_id INTEGER,
  reader_id INTEGER,
  read_at DATETIME,
  FOREIGN KEY (message_id) REFERENCES messages(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (reader_id) REFERENCES users(id) ON DELETE CASCADE ON UPDATE CASCADE
);
