SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

CREATE DATABASE IF NOT EXISTS `ias_daemon` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `ias_daemon`;

CREATE TABLE IF NOT EXISTS `areas` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `identifier` varchar(80) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  PRIMARY KEY (`id`),
  UNIQUE KEY `identifier` (`identifier`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

CREATE TABLE IF NOT EXISTS `area_devices` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `area_id` int(10) unsigned NOT NULL,
  `device_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `area_id` (`area_id`),
  KEY `device_id` (`device_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

CREATE TABLE IF NOT EXISTS `area_links` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `area_from_id` int(10) unsigned NOT NULL,
  `area_to_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `area_from_id` (`area_from_id`),
  KEY `area_to_id` (`area_to_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

CREATE TABLE IF NOT EXISTS `buildings` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `identifier` varchar(80) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  PRIMARY KEY (`id`),
  UNIQUE KEY `identifier` (`identifier`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

CREATE TABLE IF NOT EXISTS `building_areas` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `building_id` int(10) unsigned NOT NULL,
  `area_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `building_id` (`building_id`),
  KEY `area_id` (`area_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

CREATE TABLE IF NOT EXISTS `controllers` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `identifier` varchar(80) NOT NULL,
  `security_code` varchar(45) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  PRIMARY KEY (`id`),
  UNIQUE KEY `identifier_UNIQUE` (`identifier`),
  UNIQUE KEY `security_code` (`security_code`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

CREATE TABLE IF NOT EXISTS `devices` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `controller_id` int(10) unsigned NOT NULL,
  `technology_id` int(10) unsigned NOT NULL,
  `identifier` varchar(80) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  `monitor` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`controller_id`,`technology_id`),
  KEY `fk_devices_controllers1_idx` (`controller_id`),
  KEY `fk_devices_technologies1_idx` (`technology_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=13 ;

CREATE TABLE IF NOT EXISTS `device_history_states` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `device_id` int(10) unsigned NOT NULL,
  `technology_member` varchar(80) NOT NULL,
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0',
  `value` varchar(255) NOT NULL,
  PRIMARY KEY (`id`,`device_id`),
  KEY `fk_device_history_states_technology_members1_idx` (`technology_member`),
  KEY `fk_device_history_states_devices1_idx` (`device_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=59 ;

CREATE TABLE IF NOT EXISTS `nlp_dictionaries` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `identifier` varchar(80) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `identifier` (`identifier`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

CREATE TABLE IF NOT EXISTS `nlp_dictionary_contents` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `dictionary_id` int(10) unsigned NOT NULL,
  `word` varchar(50) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `word` (`word`),
  KEY `dictionary_id` (`dictionary_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=73011 ;

CREATE TABLE IF NOT EXISTS `rules` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

CREATE TABLE IF NOT EXISTS `rule_actions` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `rule_id` int(10) unsigned NOT NULL,
  `device_id` int(10) unsigned NOT NULL,
  `feature_identifier` varchar(80) NOT NULL,
  `feature_parameter` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`,`rule_id`,`feature_identifier`,`device_id`),
  KEY `fk_rule_actions_rules1_idx` (`rule_id`),
  KEY `fk_rule_actions_technology_features1_idx` (`feature_identifier`),
  KEY `fk_rule_actions_devices1_idx` (`device_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

CREATE TABLE IF NOT EXISTS `rule_conditions` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `rule_condition_set_id` int(10) unsigned NOT NULL,
  `device_id` int(10) unsigned NOT NULL,
  `operator` varchar(2) NOT NULL,
  `member` varchar(80) NOT NULL,
  `value` varchar(255) DEFAULT NULL,
  `referenced_device_id` int(10) unsigned DEFAULT NULL,
  `referenced_device_member` varchar(80) DEFAULT NULL,
  PRIMARY KEY (`id`,`rule_condition_set_id`,`device_id`),
  KEY `fk_rule_conditions_rule_condition_sets1_idx` (`rule_condition_set_id`),
  KEY `fk_rule_conditions_technology_members1_idx` (`member`),
  KEY `fk_rule_conditions_devices1_idx` (`device_id`),
  KEY `referenced_device_id` (`referenced_device_id`,`referenced_device_member`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=16 ;

CREATE TABLE IF NOT EXISTS `rule_condition_sets` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `rule_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`,`rule_id`),
  KEY `fk_rule_condition_sets_rules1_idx` (`rule_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

CREATE TABLE IF NOT EXISTS `technologies` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `identifier` varchar(80) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  PRIMARY KEY (`id`),
  UNIQUE KEY `identifier_UNIQUE` (`identifier`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

CREATE TABLE IF NOT EXISTS `technology_features` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `technology_id` int(10) unsigned NOT NULL,
  `identifier` varchar(80) NOT NULL,
  `parameter_value_type_id` int(10) unsigned DEFAULT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  PRIMARY KEY (`id`,`technology_id`),
  KEY `fk_technology_features_value_types_idx` (`parameter_value_type_id`),
  KEY `fk_technology_features_technologies1_idx` (`technology_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

CREATE TABLE IF NOT EXISTS `technology_icons` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `technology_id` int(11) unsigned NOT NULL,
  `icon_src` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `technology_id` (`technology_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

CREATE TABLE IF NOT EXISTS `technology_members` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `technology_id` int(10) unsigned NOT NULL,
  `value_type_id` int(10) unsigned NOT NULL,
  `identifier` varchar(80) NOT NULL,
  `default_value` varchar(128) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  PRIMARY KEY (`id`,`value_type_id`,`technology_id`),
  KEY `fk_technology_members_value_types1_idx` (`value_type_id`),
  KEY `fk_technology_members_technologies1_idx` (`technology_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=22 ;

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(2) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(80) NOT NULL,
  `password` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `name` varchar(128) NOT NULL,
  `surname` varchar(128) NOT NULL,
  `gender` int(11) NOT NULL DEFAULT '0',
  `rank` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username_UNIQUE` (`username`),
  UNIQUE KEY `email_UNIQUE` (`email`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

CREATE TABLE IF NOT EXISTS `value_types` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `identifier` varchar(80) NOT NULL,
  `pattern` varchar(128) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` tinytext,
  PRIMARY KEY (`id`),
  UNIQUE KEY `identifier_UNIQUE` (`identifier`),
  UNIQUE KEY `pattern_UNIQUE` (`pattern`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;


ALTER TABLE `area_devices`
  ADD CONSTRAINT `area_devices_ibfk_1` FOREIGN KEY (`area_id`) REFERENCES `areas` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `area_devices_ibfk_2` FOREIGN KEY (`device_id`) REFERENCES `devices` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `area_links`
  ADD CONSTRAINT `area_links_ibfk_1` FOREIGN KEY (`area_from_id`) REFERENCES `areas` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `area_links_ibfk_2` FOREIGN KEY (`area_to_id`) REFERENCES `areas` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `building_areas`
  ADD CONSTRAINT `building_areas_ibfk_1` FOREIGN KEY (`building_id`) REFERENCES `buildings` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `building_areas_ibfk_2` FOREIGN KEY (`area_id`) REFERENCES `areas` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `devices`
  ADD CONSTRAINT `devices_ibfk_1` FOREIGN KEY (`controller_id`) REFERENCES `controllers` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `devices_ibfk_2` FOREIGN KEY (`technology_id`) REFERENCES `technologies` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `device_history_states`
  ADD CONSTRAINT `device_history_states_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `devices` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `nlp_dictionary_contents`
  ADD CONSTRAINT `nlp_dictionary_contents_ibfk_1` FOREIGN KEY (`dictionary_id`) REFERENCES `nlp_dictionaries` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `rule_actions`
  ADD CONSTRAINT `rule_actions_ibfk_1` FOREIGN KEY (`rule_id`) REFERENCES `rules` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `rule_actions_ibfk_2` FOREIGN KEY (`device_id`) REFERENCES `devices` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `rule_conditions`
  ADD CONSTRAINT `rule_conditions_ibfk_1` FOREIGN KEY (`rule_condition_set_id`) REFERENCES `rule_condition_sets` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `rule_conditions_ibfk_2` FOREIGN KEY (`device_id`) REFERENCES `devices` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `rule_conditions_ibfk_3` FOREIGN KEY (`referenced_device_id`) REFERENCES `devices` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `rule_condition_sets`
  ADD CONSTRAINT `rule_condition_sets_ibfk_1` FOREIGN KEY (`rule_id`) REFERENCES `rules` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `technology_features`
  ADD CONSTRAINT `technology_features_ibfk_1` FOREIGN KEY (`technology_id`) REFERENCES `technologies` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `technology_features_ibfk_2` FOREIGN KEY (`parameter_value_type_id`) REFERENCES `value_types` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `technology_icons`
  ADD CONSTRAINT `technology_icons_ibfk_1` FOREIGN KEY (`technology_id`) REFERENCES `technologies` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

ALTER TABLE `technology_members`
  ADD CONSTRAINT `technology_members_ibfk_1` FOREIGN KEY (`technology_id`) REFERENCES `technologies` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  ADD CONSTRAINT `technology_members_ibfk_2` FOREIGN KEY (`value_type_id`) REFERENCES `value_types` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
