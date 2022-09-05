USE [hmkj]
GO


--DROP TABLE   table  IF EXISTS `table_log`;

 
CREATE TABLE [dbo].[table_log](
	[table_id] [int] IDENTITY(1,1) NOT NULL,
	[event_id] [int] NULL,
	[pan_id] [nchar](10) NULL,
	[zigbee_address] [nchar](10) NULL,
	[ip] [nchar](13) NULL,
	[steps] [int] NULL,
	[employee_no] [nchar](10) NULL,
	[process_no] [nchar](24) NULL,
	[model_no] [nchar](8) NULL,
	[create_time] [datetime] NULL
) ON [PRIMARY]


CREATE TABLE [dbo].[table_status](
	[table_id] [int] IDENTITY(1,1) NOT NULL,
	[message] [nvarchar](50) NULL,
 CONSTRAINT [PK_table_status] PRIMARY KEY CLUSTERED 
(
	[table_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]


CREATE TABLE [dbo].[table_device](
	[table_id] [int] IDENTITY(1,1) NOT NULL,
	[name] [varchar](20) NULL,
	[description] [varchar](20) NULL,
	[type] [tinyint] NULL,
	[ip] [nchar](16) NULL,
	[pan_id] [nchar](10) NULL,
	[zigbee_address] [nchar](10) NULL,
	[device_status] [varchar](15) NULL,
	[time] [datetime] NULL,
	[other] [varchar](20) NULL
) ON [PRIMARY]

