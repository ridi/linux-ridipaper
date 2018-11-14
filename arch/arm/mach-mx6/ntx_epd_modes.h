

//#define EPD_TIMING_ED068OG1_NUMCE3	1
//#define EPD_TIMING_ED068TG1			1


#if 1 //[
static struct fb_videomode ed060sct_mode = {
.name = "E60SCT",
.refresh = 85,
.xres = 800,
.yres = 600,
.pixclock = 26680000,
.left_margin = 8,
.right_margin = 96,
.upper_margin = 4,
.lower_margin = 13,
.hsync_len = 4,
.vsync_len = 1,
.sync = 0,
.vmode = FB_VMODE_NONINTERLACED,
.flag = 0,
};

static struct fb_videomode ed060scq_mode = {
.name = "E60SCQ",
.refresh = 85,
.xres = 800,
.yres = 600,
.pixclock = 25000000,
.left_margin = 8,
.right_margin = 60,
.upper_margin = 4,
.lower_margin = 10,
.hsync_len = 8,
.vsync_len = 4,
.sync = 0,
.vmode = FB_VMODE_NONINTERLACED,
.flag = 0,
};

static struct fb_videomode ed060sc8_mode = {
.name = "E60SC8",
.refresh = 85,
.xres = 800,
.yres = 600,
.pixclock = 30000000,
.left_margin = 8,
.right_margin = 164,
.upper_margin = 4,
.lower_margin = 18,
.hsync_len = 4,
.vsync_len = 1,
.sync = 0,
.vmode = FB_VMODE_NONINTERLACED,
.flag = 0,
};

// for ED060XC5 release by Freescale Grace 20120726 .

static struct fb_videomode ed060xc1_mode = {
.name = "E60XC1",
.refresh = 85,
.xres = 1024,
.yres = 768,
.pixclock = 40000000,
.left_margin = 12,
.right_margin = 72,
.upper_margin = 4,
.lower_margin = 5,
.hsync_len = 8,
.vsync_len = 2,
.sync = 0,
.vmode = FB_VMODE_NONINTERLACED,
.flag = 0,
};

static struct fb_videomode ed060xc5_mode = {
.name = "E60XC5",
.refresh = 85,
.xres = 1024,
.yres = 758,
.pixclock = 40000000,
.left_margin = 12,
.right_margin = 76,
.upper_margin = 4,
.lower_margin = 5,
.hsync_len = 12,
.vsync_len = 2,
.sync = 0,
.vmode = FB_VMODE_NONINTERLACED,
.flag = 0,
};

static struct fb_videomode e60_v110_mode = {
.name = "E60_V110",
.refresh = 50,
.xres = 800,
.yres = 600,
.pixclock = 18604700,
.left_margin = 8,
.right_margin = 176,
.upper_margin = 4,
.lower_margin = 2,
.hsync_len = 4,
.vsync_len = 1,
.sync = 0,
.vmode = FB_VMODE_NONINTERLACED,
.flag = 0,
};

static struct fb_videomode ed050xxx_mode = {
	.name="ED050XXXX",
	.refresh=85,
	.xres=800,
	.yres=600,
	.pixclock=26666667,
	.left_margin=4,
	.right_margin=98,
	.upper_margin=4,
	.lower_margin=9,
	.hsync_len=8,
	.vsync_len=2,
	.sync=0,
	.vmode=FB_VMODE_NONINTERLACED,
	.flag=0,
};


#ifdef EPD_TIMING_ED068TG1 //[
static struct fb_videomode ed068tg1_mode = {
.name = "ED068TG1",
.refresh=85,
.xres=1440,
.yres=1080,
.pixclock=96000000,
.left_margin=24,
.right_margin=267,
.upper_margin=4,
.lower_margin=5,
.hsync_len=24,
.vsync_len=2,
.sync=0,
.vmode=FB_VMODE_NONINTERLACED,
.flag=0,
};
#elif defined(EPD_TIMING_ED068OG1_NUMCE3) //][
/* i.MX508 waveform data timing data structures for ed068og1_numce3 */
/* Created on - Monday, October 15, 2012 10:36:24
   Warning: this pixel clock is derived from 480 MHz parent! */

static struct fb_videomode ed068og1_numce3_mode = {
.name="ED068OG1_NUMCE3",
.refresh=85,
.xres=1440,
.yres=1080,
.pixclock=96000000,
.left_margin=24,
.right_margin=267,
.upper_margin=4,
.lower_margin=5,
.hsync_len=24,
.vsync_len=2,
.sync=0,
.vmode=FB_VMODE_NONINTERLACED,
.flag=0,
};
#else
static struct fb_videomode ed068og1_mode = {
.name = "ED068TH1",
.refresh=85,
.xres=1440,
.yres=1080,
.pixclock=88000000,
.left_margin=24,
.right_margin=181,
.upper_margin=4,
.lower_margin=5,
.hsync_len=24,
.vsync_len=2,
.sync=0,
.vmode=FB_VMODE_NONINTERLACED,
.flag=0,
};
#endif//]EPD_TIMING_ED068OG1_NUMCE3

static struct fb_videomode peng060d_mode = {
.name = "PENG060D",
.refresh=85,
.xres=1448,
.yres=1072,
.pixclock=80000000,
.left_margin=16,
.right_margin=102,
.upper_margin=4,
.lower_margin=4,
.hsync_len=28,
.vsync_len=2,
.sync=0,
.vmode=FB_VMODE_NONINTERLACED,
.flag=0,
};

static struct fb_videomode ef133ut1sce_mode = {
.name="EF133UT1SCE",
.refresh=65,
.xres=1600,
.yres=1200,
.pixclock=72222223,
.left_margin=8,
.right_margin=97,
.upper_margin=4,
.lower_margin=7,
.hsync_len=12,
.vsync_len=1,
.sync=0,
.vmode=FB_VMODE_NONINTERLACED,
.flag=0,
};

static struct fb_videomode ed078kh1_mode = {
.name = "ED078KH1",
.refresh=85,
.xres=1872,
.yres=1404,
.pixclock=133400000,
.left_margin=44,
.right_margin=89,
.upper_margin=4,
.lower_margin=5,
.hsync_len=44,
.vsync_len=1,
.sync=0,
.vmode=FB_VMODE_NONINTERLACED,
.flag=0,
};



static struct imx_epdc_fb_mode panel_modes[] = {
////////////////////
{
& ed060sc8_mode,
4,            /* vscan_holdoff */
10,          /* sdoed_width */
20,          /* sdoed_delay */
10,          /* sdoez_width */
20,          /* sdoez_delay */
465,        /* gdclk_hp_offs */
250,        /* gdsp_offs changed delay to 8.3 uS */
0,            /* gdoe_offs */
8,            /* gdclk_offs changed delay to 4.5 SDCLK */
1,            /* num_ce */
},

////////////////////
{
& e60_v110_mode,
4,            /* vscan_holdoff */
10,          /* sdoed_width */
20,          /* sdoed_delay */
10,          /* sdoez_width */
20,          /* sdoez_delay */
465,        /* gdclk_hp_offs */
250,        /* gdsp_offs changed delay to 8.3 uS */
0,            /* gdoe_offs */
8,            /* gdclk_offs changed delay to 4.5 SDCLK */
1,            /* num_ce */
},

////////////////////
{
& ed060xc5_mode,
4,            /* vscan_holdoff */
10,          /* sdoed_width */
20,          /* sdoed_delay */
10,          /* sdoez_width */
20,          /* sdoez_delay */
524,        /* gdclk_hp_offs */
25,        /* gdsp_offs changed delay to 8.3 uS */
0,            /* gdoe_offs */
19,            /* gdclk_offs changed delay to 4.5 SDCLK */
1,            /* num_ce */
},

////////////////////
{
& ed060xc1_mode,
4,            /* vscan_holdoff */
10,          /* sdoed_width */
20,          /* sdoed_delay */
10,          /* sdoez_width */
20,          /* sdoez_delay */
492,        /* gdclk_hp_offs */
29,        /* gdsp_offs changed delay to 8.3 uS */
0,            /* gdoe_offs */
23,            /* gdclk_offs changed delay to 4.5 SDCLK */
1,            /* num_ce */
},

////////////////////
{
	&ed050xxx_mode, 	/* struct fb_videomode *mode */
		4, 	/* vscan_holdoff */
		10, 	/* sdoed_width */
		20, 	/* sdoed_delay */
		10, 	/* sdoez_width */
		20, 	/* sdoez_delay */
		420, 	/* GDCLK_HP */
		20, 	/* GDSP_OFF */
		0, 	/* GDOE_OFF */
		11, 	/* gdclk_offs */
		3, 	/* num_ce */
},	

#ifdef EPD_TIMING_ED068TG1 //[
{
& ed068tg1_mode,
4,            /* vscan_holdoff */
10,          /* sdoed_width */
20,          /* sdoed_delay */
10,          /* sdoez_width */
20,          /* sdoez_delay */
665,        /* GDCLK_HP */
718,        /* GDSP_OFF */
0,            /* GDOE_OFF */
199,        /* gdclk_offs */
1,            /* num_ce */
},
#elif defined(EPD_TIMING_ED068OG1_NUMCE3)//][
{
& ed068og1_numce3_mode,
4,            /* vscan_holdoff */
10,          /* sdoed_width */
20,          /* sdoed_delay */
10,          /* sdoez_width */
20,          /* sdoez_delay */
665,        /* GDCLK_HP */
210,        /* GDSP_OFF */
0,            /* GDOE_OFF */
199,        /* gdclk_offs */
3,            /* num_ce */
},
#else//][ !EPD_TIMING_ED068OG1_NUMCE3
{
& ed068og1_mode,
4,            /* vscan_holdoff */
10,          /* sdoed_width */
20,          /* sdoed_delay */
10,          /* sdoez_width */
20,          /* sdoez_delay */
609,        /* GDCLK_HP */
660,        /* GDSP_OFF */
0,            /* GDOE_OFF */
184,        /* gdclk_offs */
1,            /* num_ce */
},
#endif//] EPD_TIMING_ED068OG1_NUMCE3

{
&peng060d_mode,
4,            /* vscan_holdoff */
10,          /* sdoed_width */
20,          /* sdoed_delay */
10,          /* sdoez_width */
20,          /* sdoez_delay */
562,        /* GDCLK_HP */
662,        /* GDSP_OFF */
0,            /* GDOE_OFF */
225,        /* gdclk_offs */
3,            /* num_ce */
},
{
&ef133ut1sce_mode,
4,      /* vscan_holdoff */
10,     /* sdoed_width */
20,     /* sdoed_delay */
10,     /* sdoez_width */
20,     /* sdoez_delay */
743,    /* GDCLK_HP */
475,    /* GDSP_OFF */
0,      /* GDOE_OFF */
15,     /* gdclk_offs */
1,      /* num_ce */
},
{
&ed060scq_mode,
4,      /* vscan_holdoff */
10,     /* sdoed_width */
20,     /* sdoed_delay */
10,     /* sdoez_width */
20,     /* sdoez_delay */
438,    /* GDCLK_HP */
263,    /* GDSP_OFF */
0,      /* GDOE_OFF */
23,     /* gdclk_offs */
3,      /* num_ce */
},
{
&ed078kh1_mode,
4,      /* vscan_holdoff */
10,     /* sdoed_width */
20,     /* sdoed_delay */
10,     /* sdoez_width */
20,     /* sdoez_delay */
772,    /* GDCLK_HP */
757,    /* GDSP_OFF */
0,      /* GDOE_OFF */
199,     /* gdclk_offs */
1,      /* num_ce */
},
{
&ed060sct_mode,
4,      /* vscan_holdoff */
10,     /* sdoed_width */
20,     /* sdoed_delay */
10,     /* sdoez_width */
20,     /* sdoez_delay */
372,    /* GDCLK_HP */
367,    /* GDSP_OFF */
0,      /* GDOE_OFF */
111,     /* gdclk_offs */
1,      /* num_ce */
},
};
 

#else //][!
static struct fb_videomode e60_v110_mode = {
	.name = "E60_V110",
	.refresh = 50,
	.xres = 800,
	.yres = 600,
	.pixclock = 18604700,
	.left_margin = 8,
	.right_margin = 178,
	.upper_margin = 4,
	.lower_margin = 10,
	.hsync_len = 20,
	.vsync_len = 4,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};
static struct fb_videomode e60_v220_mode = {
	.name = "E60_V220",
	.refresh = 85,
	.xres = 800,
	.yres = 600,
	.pixclock = 30000000,
	.left_margin = 8,
	.right_margin = 164,
	.upper_margin = 4,
	.lower_margin = 8,
	.hsync_len = 4,
	.vsync_len = 1,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
	.refresh = 85,
	.xres = 800,
	.yres = 600,
};
static struct fb_videomode e060scm_mode = {
	.name = "E060SCM",
	.refresh = 85,
	.xres = 800,
	.yres = 600,
	.pixclock = 26666667,
	.left_margin = 8,
	.right_margin = 100,
	.upper_margin = 4,
	.lower_margin = 8,
	.hsync_len = 4,
	.vsync_len = 1,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};
static struct fb_videomode e97_v110_mode = {
	.name = "E97_V110",
	.refresh = 50,
	.xres = 1200,
	.yres = 825,
	.pixclock = 32000000,
	.left_margin = 12,
	.right_margin = 128,
	.upper_margin = 4,
	.lower_margin = 10,
	.hsync_len = 20,
	.vsync_len = 4,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};

static struct imx_epdc_fb_mode panel_modes[] = {
	{
		&e60_v110_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		428,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		1,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e60_v220_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		465,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		9,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e060scm_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		419,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		5,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e97_v110_mode,
		8,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		632,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		1,      /* gdclk_offs */
		3,      /* num_ce */
	}
};
#endif //]


