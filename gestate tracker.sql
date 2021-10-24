-- phpMyAdmin SQL Dump
-- version 4.1.6
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: May 26, 2021 at 03:48 PM
-- Server version: 5.6.16
-- PHP Version: 5.5.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `body_parameter`
--

-- --------------------------------------------------------

--
-- Table structure for table `info`
--

CREATE TABLE IF NOT EXISTS `info` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `PulseRate` varchar(50) NOT NULL,
  `SystolicBP` varchar(50) NOT NULL,
  `DiastolicBP` varchar(50) NOT NULL,
  `O2Saturation` varchar(50) NOT NULL,
  `TotalHemoglobin` varchar(50) NOT NULL,
  `Temperature` varchar(50) NOT NULL,
  `DateTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `info`
--

INSERT INTO `info` (`id`, `PulseRate`, `SystolicBP`, `DiastolicBP`, `O2Saturation`, `TotalHemoglobin`, `Temperature`, `DateTime`) VALUES
(1, '75', '129.37', '81.71', '17', '23.45', '94.96', '2021-05-26 04:20:28'),
(2, '95', '107.12', '82.30', '89', '15.54', '94.25', '2021-05-26 04:22:06');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
