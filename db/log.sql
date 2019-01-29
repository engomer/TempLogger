-- phpMyAdmin SQL Dump
-- version 3.4.10
-- http://www.phpmyadmin.net
--
-- Host: 94.73.146.24
-- Generation Time: Jan 26, 2019 at 05:00 PM
-- Server version: 1.0.221
-- PHP Version: 5.2.6-1+lenny10

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `db_ogencay_com`
--

-- --------------------------------------------------------

--
-- Table structure for table `log`
--

CREATE TABLE IF NOT EXISTS `log` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `timestamp` timestamp NOT NULL DEFAULT current_timestamp(),
  `tempin` varchar(20) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `tempout` varchar(20) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `hum` varchar(20) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=71 ;

--
-- Dumping data for table `log`
--

INSERT INTO `log` (`id`, `timestamp`, `tempin`, `tempout`, `hum`) VALUES
(1, '2019-01-22 19:57:21', '24.81', '25.00', '44.00'),
(2, '2019-01-22 19:59:21', '25.00', '25.00', '43.00'),
(3, '2019-01-22 20:01:22', '24.94', '25.00', '43.00'),
(4, '2019-01-22 20:06:50', '24.56', '25.00', '42.00'),
(5, '2019-01-22 20:50:28', '24.81', '25.00', '44.00'),
(6, '2019-01-22 22:06:58', '26.44', '27.00', '42.00'),
(7, '2019-01-22 23:35:50', '36.06', '38.00', '20.00'),
(8, '2019-01-23 00:52:19', '25.25', '26.00', '41.00'),
(9, '2019-01-23 02:08:58', '23.94', '25.00', '42.00'),
(10, '2019-01-23 03:25:37', '23.56', '25.00', '42.00'),
(11, '2019-01-23 04:42:17', '23.50', '25.00', '43.00'),
(12, '2019-01-23 05:58:56', '24.37', '25.00', '49.00'),
(13, '2019-01-23 07:15:35', '24.12', '25.00', '46.00'),
(14, '2019-01-23 08:32:14', '24.12', '25.00', '45.00'),
(15, '2019-01-23 09:48:53', '24.06', '25.00', '44.00'),
(16, '2019-01-23 11:05:32', '23.94', '25.00', '47.00'),
(17, '2019-01-23 12:22:11', '25.00', '26.00', '48.00'),
(18, '2019-01-23 13:38:50', '25.25', '26.00', '44.00'),
(19, '2019-01-23 14:55:29', '24.69', '25.00', '45.00'),
(20, '2019-01-23 16:12:08', '24.37', '25.00', '44.00'),
(21, '2019-01-23 17:28:47', '24.19', '25.00', '44.00'),
(22, '2019-01-23 18:45:26', '24.12', '25.00', '44.00'),
(23, '2019-01-23 20:02:05', '24.19', '25.00', '48.00'),
(24, '2019-01-23 21:18:44', '24.12', '25.00', '45.00'),
(25, '2019-01-23 22:35:23', '24.00', '25.00', '46.00'),
(26, '2019-01-23 23:52:02', '24.06', '25.00', '47.00'),
(27, '2019-01-24 00:58:17', '24.00', '25.00', '46.00'),
(28, '2019-01-24 02:14:46', '24.00', '25.00', '46.00'),
(29, '2019-01-24 03:31:26', '24.06', '25.00', '46.00'),
(30, '2019-01-24 04:48:05', '24.06', '25.00', '45.00'),
(31, '2019-01-24 06:04:44', '24.12', '25.00', '46.00'),
(32, '2019-01-24 07:21:23', '24.06', '25.00', '46.00'),
(33, '2019-01-24 08:38:02', '24.06', '25.00', '45.00'),
(34, '2019-01-24 09:54:41', '24.37', '25.00', '46.00'),
(35, '2019-01-24 11:11:20', '24.25', '25.00', '44.00'),
(36, '2019-01-24 12:27:59', '24.06', '25.00', '43.00'),
(37, '2019-01-24 13:37:36', '85.00', '25.00', '39.00'),
(38, '2019-01-24 14:55:45', '24.12', '25.00', '40.00'),
(39, '2019-01-24 16:12:24', '24.06', '25.00', '40.00'),
(40, '2019-01-24 17:29:03', '24.06', '25.00', '40.00'),
(41, '2019-01-24 18:45:41', '24.06', '25.00', '40.00'),
(42, '2019-01-24 20:02:20', '24.00', '25.00', '40.00'),
(43, '2019-01-24 21:18:59', '24.06', '25.00', '41.00'),
(44, '2019-01-25 02:27:38', '25.44', '26.00', '45.00'),
(45, '2019-01-25 13:26:34', '24.31', '25.00', '47.00'),
(46, '2019-01-25 14:50:03', '24.56', '25.00', '47.00'),
(47, '2019-01-25 16:13:31', '24.50', '25.00', '46.00'),
(48, '2019-01-25 17:36:59', '24.37', '25.00', '46.00'),
(49, '2019-01-25 19:00:27', '24.31', '25.00', '46.00'),
(50, '2019-01-25 20:23:55', '24.37', '25.00', '47.00'),
(51, '2019-01-25 22:34:23', '24.87', '26.00', '50.00'),
(52, '2019-01-26 00:32:17', '24.31', '26.00', '45.00'),
(53, '2019-01-26 01:40:57', '23.94', '25.00', '45.00'),
(54, '2019-01-26 02:49:42', '23.75', '25.00', '45.00'),
(55, '2019-01-26 03:58:27', '23.62', '25.00', '45.00'),
(56, '2019-01-26 05:07:12', '23.62', '25.00', '44.00'),
(57, '2019-01-26 06:15:57', '23.56', '25.00', '44.00'),
(58, '2019-01-26 07:24:42', '23.56', '25.00', '44.00'),
(59, '2019-01-26 08:33:27', '23.56', '25.00', '44.00'),
(60, '2019-01-26 09:42:11', '23.56', '25.00', '44.00'),
(61, '2019-01-26 10:50:56', '23.62', '25.00', '43.00'),
(62, '2019-01-26 11:59:41', '23.69', '25.00', '41.00'),
(63, '2019-01-26 13:08:26', '24.63', '26.00', '43.00'),
(64, '2019-01-26 14:17:11', '24.00', '26.00', '40.00'),
(65, '2019-01-26 15:25:56', '23.69', '25.00', '40.00'),
(66, '2019-01-26 16:34:41', '23.56', '25.00', '40.00'),
(67, '2019-01-26 17:43:26', '23.50', '25.00', '40.00'),
(68, '2019-01-26 18:52:11', '23.44', '25.00', '40.00'),
(69, '2019-01-26 20:00:56', '23.62', '25.00', '38.00'),
(70, '2019-01-26 21:09:41', '23.81', '25.00', '35.00');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;