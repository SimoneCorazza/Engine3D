#pragma once

//Indica come il cursore verrà trattato dall'applicazione
enum IE_CursorMode
{
	IE_CursorMode_Normal, //Cursore visualizzato come da sistema operativo
	IE_CursorMode_Hide, //Cursore nascosto (non visualizzato)
	IE_CursorMode_Disabled, //Cursore disabilitato (adatto per una camera 3D)
};